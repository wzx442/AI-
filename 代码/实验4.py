"""
Created on Fri Nov 18 08:53:26 2022
@author: 44201
#请使用spyder运行,使用pycharm会缺少输出图像
"""

# https://blog.csdn.net/weixin_43840511/article/details/114897769


import random
import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import cholesky

if __name__ == '__main__':

    base = 10.0
    data = []
    alldata = []
    N = 6

    num = 0
    while num < N:

        alpha1 = np.array([[random.randint(5, 95), random.randint(5, 95)]])  # 生成随机数据
        Sigma = np.array([[8, 5], [3, 2]])
        rou = cholesky(Sigma)
        alpha = np.dot(np.random.randn(6, 2), rou) + alpha1

        key = False
        for i in alpha.tolist():
            for j in alldata:
                if abs(i[0] - j[0]) + abs(i[1] - j[1]) <= 10:
                    key = True
                    break
        if key:  # 随机数据碰撞则重来
            continue
        num += 1

        plt.plot(alpha[:, 0], alpha[:, 1], '*', markersize=10)

        x = []
        for i in alpha:
            x.append(np.array(np.hstack((np.array(i), np.array([base])))))

        data.append(np.array(x))

        for i in alpha.tolist():
            alldata.append(i)

    wlist = []
    for i in range(0, N):
        wlist.append(np.array([base, base, base]))  # 初始权向量

    ccc = 0
    while True:
        time = 0

        for i in range(0, N):
            for yi in data[i]:
                for t in range(0, N):
                    if t == i:
                        continue

                    while np.dot(yi, wlist[i]) <= np.dot(yi, wlist[t]) + 0.5:  # 修正
                        wlist[i] += np.array(yi)
                        wlist[t] -= np.array(yi)
                        time += 1

        if time == 0:
            break

    for i in wlist:
        for j in wlist:
            if (i == j).all():
                continue
            linex = np.array([0.0, 100.0])
            plt.plot(linex, (((-1) * linex * (i[0] - j[0]) - base * (i[2] - j[2])) / (i[1] - j[1])), alpha=0.5)  # 画分割线

    plt.xlim(0, 100)
    plt.ylim(0, 100)
    plt.show()

    plt.cla()

    picx = []
    picy = []
    for i in range(0, N):
        picx.append([])
        picy.append([])

    for i in range(0, 100):
        for j in range(0, 100):

            maxx = []
            for t in wlist:
                maxx.append(np.dot(np.array([i, j, base]), t))

            k = maxx.index(max(maxx))
            picx[k].append(i)
            picy[k].append(j)

        for i in data:
            plt.plot(i[:, 0], i[:, 1], '*', markersize=10)  #
        
    for i in range(0, N):
        plt.plot(picx[i], picy[i], '.', alpha=0.3)  # 画出各个位置上的预测结果
        # plt.show()
