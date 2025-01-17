%%
%�����򣬳���Ӵ˿�ʼ
clc,clear  
npersons=40;%ѡȡ40���˵���  
global imgrow;  
global imgcol;  
imgrow=112;  
imgcol=92;  
%%
%��ȡѵ������ 
disp('��ȡѵ������...')  
[f_matrix,train_label]=ReadFace(npersons,0);%��ȡѵ������  
nfaces=size(f_matrix,1);%��������������  
disp('.................................................')  
%��ά�ռ��ͼ����(nperson*5)*k�ľ���ÿ�д���һ�����ɷ�����ÿ����20ά����  
%%
%��ѵ�������н�ά����
disp('ѵ������PCA������ȡ...')  
mA=mean(f_matrix);  
k=50;%��ά��20ά  ��ȷ��84%
%k=25;%��ά��25ά ��ȷ��86.5%
%k=50;%��ά��50ά ��ȷ��88%
%k=100;%��ά��100ά ��ȷ��88.5%
%k=200;%��ά��200ά ��ȷ��89%
%����������Э��������ά����10304ά����ѵ��������������ֻ��200
%��ô�����õ�����ֵ��Ӧ����������С�ڵ���199�������������������Ӧ������ֵ��Ϊ0
[train_pcaface,V]=fastPCA(f_matrix,k,mA);%���ɷַ�����������ȡ  
%train_pcaface��ά��ѵ�������ڵ�ά�ռ��е�ϵ�������ʾ 
%V-���ɷַ���������ά�ռ䵱�еĻ�  
disp('.................................................')  

%%
%��ʾ���ɷ�����������������ά�Ļ�
disp('��ʾ���ɷ���...')  
visualize(V,k)%��ʾ��������  ,��������
disp('.................................................')  
  
%%
%��άѵ������һ��
disp('ѵ���������ݹ�һ��...')  
disp('.................................................')  
lowvec=min(train_pcaface);  
upvec=max(train_pcaface);  
train_scaledface = scaling( train_pcaface,lowvec,upvec);  
 
%%
%SVM����ѵ��
%���˵ĳ����Դ�����иĶ���ʹ�õ���libsvm���������SVM����
disp('SVM����ѵ��...')  
disp('.................................................')  
%model = svmtrain(train_scaledface,train_label,'kernel_function','linear');
model = svmtrain(train_label,train_scaledface,'-t 0');
%model = fitcsvm(train_label,train_scaledface);
 %%
 %��ȡ��������
disp('��ȡ��������...')  
disp('.................................................')  
[test_facedata,test_facelabel]=ReadFace(npersons,1);  
  
%%
%�������ݽ�ά
%test_pcatestface-�������ݵ�ά�ռ�ı�ʾ
disp('��������������ά...')  
disp('.................................................')  
m=size(test_facedata,1);  
for i=1:m  
    test_facedata(i,:)=test_facedata(i,:)-mA;  
end  
test_pcatestface=test_facedata*V;  
  
%%
%�������ݹ�һ��
disp('�����������ݹ�һ��...')  
disp('.................................................')  
scaled_testface = scaling( test_pcatestface,lowvec,upvec);  
  
%%
%����ѵ����������ģ�ͣ��Բ��Լ����з���
disp('SVM��������...')  
disp('.................................................')  
[predict_label,accuracy,decision_values]=svmpredict(test_facelabel,scaled_testface,model);

%%
%����ʶ��ģ��
disp('����ʶ��ģ��')
disp('.................................................')  
recognition(mA,V,model) ;