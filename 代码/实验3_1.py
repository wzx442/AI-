import numpy as np
import matplotlib.pyplot as plt

def fisher(X,y):
    [row,col]=np.shape(X)
    N1=int(np.sum(y==1))
    N2=col -N1
    X1=X[:row,y==1]
    X2=X[:row,y==0]
    
    #��X1��X2ת�ɾ���
    X1=np.mat(X1)
    X2=np.mat(X2)
    m1=np.mean(X1,axis=1)
    m2=np.mean(X2,axis=1)
    
    #��������������ɢ�Ⱦ���Si(S1 S2)��Sw
    S1=np.zeros((row,row))
    S2=np.zeros((row,row))
    for i in range(N1):
        temp=X1[:,i]-m1
        S1=S1+temp*temp.T 

    for i in range(N2):
        temp=X2[:,i]-m2
        S2+=np.dot(temp,np.transpose(temp))
   
    Sw=S1+S2
  
    # �������������ɢ�Ⱦ���Sb
    Sb=np.dot(m1-m2,np.transpose(m1-m2))
    
    #������W
    W= np.linalg.inv(Sw) * (m1-m2)
    
    #����ֵy0
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

def decision(W,y0,X): #X������һ�е�����
    t=X*W-y0
    if t>=0:
        print('�ϸ�')
    else:
        print('���ϸ�')
      

def Plot_Org2(X,y):  
    #������άԭʼ��ķֲ�
    [row,col]=np.shape(X)
    N1=int(np.sum(y==1))
    N2=col -N1
    X1=X[:row,y==1]
    X2=X[:row,y==0]
    plt.figure()
    plt.rcParams['font.sans-serif']=['SimHei']
    plt.rcParams['axes.unicode_minus'] = False  #matplotlib��ͼ��������ʾ�������⣬��Ҫ����������Ĭ������
    plt.xlabel('X')
    plt.ylabel('Y')
    colors1 = '#0000FF' #�����ɫ
    colors2 = '#DC143C'
    area = np.pi * 4**2  # ����� 
    plt.scatter(np.array(X1[0,:]),np.array(X1[1,:]) , s=area, c=colors1, alpha=0.4,label='�ϸ�')
    plt.scatter(np.array(X2[0,:]),np.array(X2[1,:]), s=area, c=colors2, alpha=0.4,label='���ϸ�')
    plt.legend()
    plt.show()
    
def Plot_Des(X,y,W):   
    #��ת�����һά����
    [row,col]=np.shape(X)
    N1=int(np.sum(y==1))
    N2=col -N1
    X1=X[:row,y==1]
    X2=X[:row,y==0]
    y1=np.dot(np.transpose(W),X1)
    y2=np.dot(np.transpose(W),X2)
    
    #ת��Ϊһά���겢�����ֵ
    colors1 = '#0000FF' #�����ɫ
    colors2 = '#DC143C'
    area = np.pi * 4**2  # ����� 
    plt.figure()
    plt.scatter(np.array(y1),np.ones(np.size(y1)) , s=area, c=colors1, alpha=0.4,label='�ϸ�')
    plt.scatter(np.array(y2),np.zeros(np.size(y2)), s=area, c=colors2, alpha=0.4,label='���ϸ�')
    plt.vlines(y0,0, 1, colors = "c", linestyles = "dashed")
    plt.legend()
    plt.show()

if __name__ == '__main__':
    #��������  
    data=np.array([2.95,2.53,3.57,3.16,2.58,2.16,3.27,6.63,7.79,5.65,5.47,4.46,6.22,3.52, 1,1,1,1,0,0,0]).reshape(3,7)
    print(data.shape)
    print(data)
    X=data[:2,:]
    y=data[2,:]
    print('��������Ϊ��',X)
    print('�����ǩΪ��',y)
    W,y0=fisher(X, y)
    print("����w*Ϊ:",W)
    print("��ֵy0Ϊ:",y0)
    Plot_Org2(X,y)  #����ԭʼ����
    Plot_Des(X,y,W) #����һά���ݺ���ֵ
    while True:       
        n1,n2= map(float,input('������һ������������').split())
        if n1==0 and n2==0:
            print('����')
            break
        n=np.mat([n1,n2])
        decision(W,y0,n)