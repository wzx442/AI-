function visualize(B,k)  
%显示特征脸（变换空间中的基向量，即单位特征向量）  
%输入：B——每列是个主成分分量，显示的就是低维中每个基组成的图像  
%     k——主成分的维数  
global imgrow;  
global imgcol;  
figure  
img=zeros(imgrow,imgcol);  
for i=1:k  
    img(:)=B(:,i);  
    subplot(4,ceil(k/4),i);  
    imshow(img,[])  
end  
end  