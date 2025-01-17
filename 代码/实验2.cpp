#include<stdio.h>
#include<string.h>
//#include <windows.h>
int chess[3][3];
int x,y,count;

/*
��ҷ��õ�λ����Ϊ-1
�㷨���õ�λ����Ϊ1
���ΪMIN
�㷨ΪMAX
*/ 

int IsWin()//�ж���Ӯ���� 
{
	int i;
	for(i=0;i<3;i++)
	{//˭���������� 
		if(chess[i][0]==1 && chess[i][1]==1 && chess[i][2]==1) return 1;//�㷨ʤ�� 
		if(chess[i][0]==-1 && chess[i][1]==-1 && chess[i][2]==-1) return -1;//���ʤ�� 
	}

	for(i=0;i<3;i++)
	{//˭���������� 
		if(chess[0][i]==1 && chess[1][i]==1 && chess[2][i]==1) return 1;
		if(chess[0][i]==-1 && chess[1][i]==-1 && chess[2][i]==-1) return -1;
	}

	//˭б�������� 
	if((chess[0][0]==1&&chess[1][1]==1&&chess[2][2]==1)||(chess[2][0]==1&&chess[1][1]==1&&chess[0][2]==1)) return 1;
    if((chess[0][0]==-1&&chess[1][1]==-1&&chess[2][2]==-1)||(chess[2][0]==-1&&chess[1][1]==-1&&chess[0][2]==-1)) return -1;

	return 0;
}

int Evaluation()//���ۺ��� 
{
	int i,j,temp[3][3];

	x=y=0;
	for(i=0;i<3;i++)//max��ʤ���� 
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==0) temp[i][j]=1;//���ŵ����̵���max���� 
			else temp[i][j]=chess[i][j];//��������λ��ֱ�Ӹ�ֵ��temp 
		}
	}
 
	for(i=0;i<3;i++)
	{//����������ʱxΪ1������С��1 
		x+=(temp[i][0]+temp[i][1]+temp[i][2])/3;
	}

	for(i=0;i<3;i++)
	{//����������ʱxΪ1������С��1 
		x+=(temp[0][i]+temp[1][i]+temp[2][i])/3;
	}

	//��б��ͬ�� 
	x+=(temp[0][0]+temp[1][1]+temp[2][2])/3;
	x+=(temp[2][0]+temp[1][1]+temp[0][2])/3;



	for(i=0;i<3;i++)//min����ң���ʤ���� 
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==0) temp[i][j]=-1;
			else temp[i][j]=chess[i][j];
		}
	}


	for(i=0;i<3;i++)
	{
		y+=(temp[i][0]+temp[i][1]+temp[i][2])/3;
	}

	for(i=0;i<3;i++)
	{
		y+=(temp[0][i]+temp[1][i]+temp[2][i])/3;
	}

	y+=(temp[0][0]+temp[1][1]+temp[2][2])/3;
	y+=(temp[2][0]+temp[1][1]+temp[0][2])/3;

	return x+y;//��ͬ��e(p)=max-min,��Ϊmin��y��Ϊ��ֵ 
}

//�ù��ֱ����ת����x,y��λ�õĺ���
//void gotoxy(int x, int y)
//{
//    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD pos;
//    pos.X = x;
//    pos.Y = y;
//    SetConsoleCursorPosition(handle, pos);
//}

//���ع�꺯��
//void HideCursor()
//{
//    CONSOLE_CURSOR_INFO cursor_info = {1,0};//�ڶ���ֵΪ0��ʾ���ع��
//    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
//}

int AlphaBeta(int &value,int deep,bool MAX)
{
	bool prune=false;
	int i,j,flag,temp;        
     
    if(deep==3 || deep+count==9){
        return Evaluation();
    }

    if(IsWin()==1){//max��ʤ
        value=10000;
        return 0;
    }

    if(MAX)//maxΪtrue����ǰΪmax�ڵ�                  
        flag=10000;
    else//��ǰΪmin�ڵ� 
        flag=-10000;
        
    for(i=0; i<3 && !prune; i++){
        for(j=0;j<3 && !prune;j++){
            if(chess[i][j]==0){
                if(MAX){//Ϊmax�ڵ�
                    chess[i][j]=-1;

                    if(IsWin()==-1)//���ʤ�� 
                        temp=-10000;
                    else
                        temp=AlphaBeta(flag,deep+1,!MAX);

                    if(temp<flag) flag=temp;//beta�ڵ�            
                    if(flag<=value) prune=true;//                 
                }
                else{
                    chess[i][j]=1;
                    
                    if(IsWin()==1)
                        temp=10000;
                    else
                        temp=AlphaBeta(flag,deep+1,!MAX);

                    if(temp>flag) flag=temp;                     
                    if(flag>=value) prune=true;
                       
                }
                chess[i][j]=0;
            }
        }
    }
    
    if(MAX){//��ǰΪmax�ڵ�
        if(flag>value)//����alphaֵ 
            value=flag;
    }
    else{//��ǰΪmin�ڵ�
        if(flag<value)//����betaֵ 
            value=flag;
    }

    return flag;
}

void PlayerInput()//������� 
{
	int row,col;
	while(true)
	{
		printf("\nYou move it at(x y):");
		scanf("%d%d",&row,&col);

		if(row>0&&row<4&&col>0&&col<4&&chess[row-1][col-1]==0)
		{
			chess[row-1][col-1]=-1;
			break;
		}
		else
		{
			printf("Input Error!\n");
		}
	}
}

void PrintChess()
{
	int i,j;
	printf("-------------------\n");
	printf("|     |     |     |\n");

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(chess[i][j]==0)printf("|     ");
			else if(chess[i][j]==1)printf("|  X  ");
			else if(chess[i][j]==-1)printf("|  O  ");
		}
		printf("|\n");
		printf("|     |     |     |\n");
		printf("-------------------\n");
		if(i<2)printf("|     |     |     |\n");	
	}
}

int PlayChess()
{
	int row,col,temp;
	int m=-10000,value=-10000,deep=1;
 
	count=0;
	memset(chess,0,sizeof(chess));
	printf("ChessBoard:\n");
	PrintChess();

	while(true)
	{
		printf("\nWho take the first step:\n1)Player.  2)Computer.[ ]\b\b");
		scanf("%d",&temp);
		if(temp!=1 && temp!=2) getchar();
		else break;
	}

	if(temp==1){ //������� 
		while(true){
			PlayerInput();
			//gotoxy(0, 0);
			PrintChess();
			count++;
			Evaluation();
			
			if(y==0){//����Ѿ�û���˿��Ի�ʤ�ľ�����  
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
			if (IsWin()==-1){//��һ�ʤ 
				printf("\nCongratulations,you win!\n");
				return 0;
			}

			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(chess[i][j]==0){
						chess[i][j]=1;//�����㷨������������λ�� 
						AlphaBeta(value,deep,1);//�ݹ���Ц�-�¼�֦ 

						if(IsWin()==1){//�㷨������������λ����ʹ�����ʤ 
						//	gotoxy(0, 0);
							printf("\nComputer put it at:%d %d\n",i+1,j+1);
							PrintChess();
							printf("\nOh,the computer win!\n");
							return 0;
						}

						if(value>m){//����m��alpha�� 
							m=value;
							row=i;//��ǰ���н� 
							col=j;//��ǰ���н�
						}
						value=-10000;
						chess[i][j]=0;
					}
				}
			}
			if(chess[row][col]){
				printf("\nCongratulations,you win!\n");
				return 0;
			}
			chess[row][col]=1;
	   
			value=-10000;
			m=-10000;
			deep=1;
		//	gotoxy(0, 0);
	        printf("\nComputer put it at:%d %d\n",row+1,col+1);
			PrintChess();
			count++;
			Evaluation();
			
			if(y==0){
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
		}
	}
	else{//�㷨����
		while(true){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(chess[i][j]==0){
						chess[i][j]=1;
						AlphaBeta(value,deep,1);//max�ڵ� 

						if(IsWin()==1){
					//		gotoxy(0, 0);
							printf("\nComputer put it at:%d %d\n",i+1,j+1);
							PrintChess();
							printf("\nOh,the computer win!\n");
							return 0;
						}

						if(value>m){
							m=value;
							row=i;
							col=j;
						}
						value=-10000;
						chess[i][j]=0;
					}
				}
			}
			chess[row][col]=1;
	   
			value=-10000;
			m=-10000;
			deep=1;
		//	gotoxy(0, 0);
	        printf("\nComputer put it at:%d %d\n",row+1,col+1);
			PrintChess();
			count++;
			Evaluation();
			
			if(x==0){//���� 
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
				
			PlayerInput();
			PrintChess();
			count++;
			Evaluation();
			
			if(x==0){
				printf("\nThe game ended in a tie!\n");
				return 0;
			}

			if (IsWin()==-1){
				printf("\nCongratulations,you win!.\n");
				return 0;
			}
		}
	}
	
	return 0;
}

int main()
{
//	HideCursor();//�������ݳ�ʼ�����ֵ���
	int k;
	while(true)
	{
		PlayChess();
		printf("\nTry Again?\n1)Yeah.\t2)Exit.[ ]\b\b");
		scanf("%d",&k); 
		if(k!=1 && k!=2) getchar();
		if(k==2) break;
	}
	return 0;
}
