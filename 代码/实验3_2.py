import numpy as np
import matplotlib.pyplot as plt
import os
from PIL import Image

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

def decision(W,y0,X): 
    t=X*W-y0
    if t>=0:
        print('���Խ��Ϊ��һ����')
    else:
        print('���Խ��Ϊ�ڶ�����')

    
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
    plt.scatter(np.array(y2),np.zeros(np.size(y2)), s=
                area, c=colors2, alpha=0.4,label='���ϸ�')
    plt.vlines(y0,0, 1, colors = "c", linestyles = "dashed")
    plt.legend()
    plt.show()

def Read_Img(filepath):
    train_set = np.zeros(shape=[1,112*92])
    for root, dirs, files in os.walk(filepath):
        for file in files:
            if os.path.splitext(file)[1] == '.pgm':
              #  print(os.path.join(root, file)) #����ļ���
                img = Image.open(os.path.join(root, file))
                # img.show()
                res=np.array(img)
                sp = res.shape
                res_1 = res.reshape(1,sp[0]*sp[1])       #����ʾͼƬ�Ķ�ά����ת����һά
                train_set=np.vstack((train_set,res_1)) 
    train_set = np.delete(train_set,0,axis=0)
    return train_set

if __name__ == '__main__':
    #�������� 
    X1 = Read_Img('OLR����/s1')
    X2 = Read_Img('OLR����/s2')
    # �ڴ��������������� ���� ��������Ϊ��SimHei�����壩
    plt.rcParams['font.sans-serif']=['SimHei'] # ����������ʾ���ı�ǩ�������������⣩
    print('X1.shape:',X1.shape)
    X=np.vstack((X1,X2)) 
    X=X.T
    print('X.shape:',X.shape)
    y1=np.ones(X1.shape[0])
    y2=np.zeros(X2.shape[0])
    y=np.hstack((y1,y2)) 
    W,y0=fisher(X, y)
    Plot_Des(X,y,W)
    print("����w*Ϊ:",W)
    print("��ֵy0Ϊ:",y0)
    test=Read_Img('OLR����/test1')
    decision(W,y0,test[0])
    decision(W,y0,test[1])