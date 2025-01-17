import numpy as np
import matplotlib.pyplot as plt

def fisher(X,y):
    [row,col]=np.shape(X)
    N1=int(np.sum(y==1))
    N2=col -N1
    X1=X[:row,y==1]
    X2=X[:row,y==0]
    
    #将X1，X2转成矩阵
    X1=np.mat(X1)
    X2=np.mat(X2)
    m1=np.mean(X1,axis=1)
    m2=np.mean(X2,axis=1)
    
    #计算样本类内离散度矩阵Si(S1 S2)和Sw
    S1=np.zeros((row,row))
    S2=np.zeros((row,row))
    for i in range(N1):
        temp=X1[:,i]-m1
        S1=S1+temp*temp.T 

    for i in range(N2):
        temp=X2[:,i]-m2
        S2+=np.dot(temp,np.transpose(temp))
   
    Sw=S1+S2
  
    # 计算样本类间离散度矩阵Sb
    Sb=np.dot(m1-m2,np.transpose(m1-m2))
    
    #求向量W
    W= np.linalg.inv(Sw) * (m1-m2)
    
    #求阈值y0
    M1=0
    for i in range(N1):
        M1+=W.T*X1[:,i]
    M1/=N1

    M2=0
    for i in range(N2):
        M2+=W.T*X2[:,i]
    M2/=N2
   
    y0=(M1*N1+M2*N2)/(N1+N2)
    
    return W,y0

def decision(W,y0,X): #X是两行一列的样本
    t=X*W-y0
    if t>=0:
        print('合格')
    else:
        print('不合格')
      

def Plot_Org2(X,y):  
    #画出二维原始点的分布
    [row,col]=np.shape(X)
    N1=int(np.sum(y==1))
    N2=col -N1
    X1=X[:row,y==1]
    X2=X[:row,y==0]
    plt.figure()
    plt.rcParams['font.sans-serif']=['SimHei']
    plt.rcParams['axes.unicode_minus'] = False  #matplotlib画图中中文显示会有问题，需要这两行设置默认字体
    plt.xlabel('X')
    plt.ylabel('Y')
    colors1 = '#0000FF' #点的颜色
    colors2 = '#DC143C'
    area = np.pi * 4**2  # 点面积 
    plt.scatter(np.array(X1[0,:]),np.array(X1[1,:]) , s=area, c=colors1, alpha=0.4,label='合格')
    plt.scatter(np.array(X2[0,:]),np.array(X2[1,:]), s=area, c=colors2, alpha=0.4,label='不合格')
    plt.legend()
    plt.show()
    
def Plot_Des(X,y,W):   
    #求转化后的一维坐标
    [row,col]=np.shape(X)
    N1=int(np.sum(y==1))
    N2=col -N1
    X1=X[:row,y==1]
    X2=X[:row,y==0]
    y1=np.dot(np.transpose(W),X1)
    y2=np.dot(np.transpose(W),X2)
    
    #转化为一维坐标并标出阈值
    colors1 = '#0000FF' #点的颜色
    colors2 = '#DC143C'
    area = np.pi * 4**2  # 点面积 
    plt.figure()
    plt.scatter(np.array(y1),np.ones(np.size(y1)) , s=area, c=colors1, alpha=0.4,label='合格')
    plt.scatter(np.array(y2),np.zeros(np.size(y2)), s=area, c=colors2, alpha=0.4,label='不合格')
    plt.vlines(y0,0, 1, colors = "c", linestyles = "dashed")
    plt.legend()
    plt.show()

if __name__ == '__main__':
    #导入数据  
    data=np.array([2.95,2.53,3.57,3.16,2.58,2.16,3.27,6.63,7.79,5.65,5.47,4.46,6.22,3.52, 1,1,1,1,0,0,0]).reshape(3,7)
    print(data.shape)
    print(data)
    X=data[:2,:]
    y=data[2,:]
    print('样本数据为：',X)
    print('分类标签为：',y)
    W,y0=fisher(X, y)
    print("向量w*为:",W)
    print("阈值y0为:",y0)
    Plot_Org2(X,y)  #画出原始数据
    Plot_Des(X,y,W) #画出一维数据和阈值
    while True:       
        n1,n2= map(float,input('请输入一个测试样本：').split())
        if n1==0 and n2==0:
            print('结束')
            break
        n=np.mat([n1,n2])
        decision(W,y0,n)