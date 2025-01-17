#include<stdio.h>
#include<string.h>
//#include <windows.h>
int chess[3][3];
int x,y,count;

/*
玩家放置的位置置为-1
算法放置的位置置为1
玩家为MIN
算法为MAX
*/ 

int IsWin()//判断输赢函数 
{
	int i;
	for(i=0;i<3;i++)
	{//谁横向连城线 
		if(chess[i][0]==1 && chess[i][1]==1 && chess[i][2]==1) return 1;//算法胜利 
		if(chess[i][0]==-1 && chess[i][1]==-1 && chess[i][2]==-1) return -1;//玩家胜利 
	}

	for(i=0;i<3;i++)
	{//谁竖向连成线 
		if(chess[0][i]==1 && chess[1][i]==1 && chess[2][i]==1) return 1;
		if(chess[0][i]==-1 && chess[1][i]==-1 && chess[2][i]==-1) return -1;
	}

	//谁斜向连成线 
	if((chess[0][0]==1&&chess[1][1]==1&&chess[2][2]==1)||(chess[2][0]==1&&chess[1][1]==1&&chess[0][2]==1)) return 1;
    if((chess[0][0]==-1&&chess[1][1]==-1&&chess[2][2]==-1)||(chess[2][0]==-1&&chess[1][1]==-1&&chess[0][2]==-1)) return -1;

	return 0;
}

int Evaluation()//估价函数 
{
	int i,j,temp[3][3];

	x=y=0;
	for(i=0;i<3;i++)//max获胜估价 
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==0) temp[i][j]=1;//空着的棋盘当作max放置 
			else temp[i][j]=chess[i][j];//其他棋盘位置直接赋值给temp 
		}
	}
 
	for(i=0;i<3;i++)
	{//横行连成线时x为1，否则小于1 
		x+=(temp[i][0]+temp[i][1]+temp[i][2])/3;
	}

	for(i=0;i<3;i++)
	{//竖行连成线时x为1，否则小于1 
		x+=(temp[0][i]+temp[1][i]+temp[2][i])/3;
	}

	//两斜行同上 
	x+=(temp[0][0]+temp[1][1]+temp[2][2])/3;
	x+=(temp[2][0]+temp[1][1]+temp[0][2])/3;



	for(i=0;i<3;i++)//min（玩家）获胜估价 
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

	return x+y;//等同于e(p)=max-min,因为min（y）为负值 
}

//让光标直接跳转到（x,y）位置的函数
//void gotoxy(int x, int y)
//{
//    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD pos;
//    pos.X = x;
//    pos.Y = y;
//    SetConsoleCursorPosition(handle, pos);
//}

//隐藏光标函数
//void HideCursor()
//{
//    CONSOLE_CURSOR_INFO cursor_info = {1,0};//第二个值为0表示隐藏光标
//    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
//}

int AlphaBeta(int &value,int deep,bool MAX)
{
	bool prune=false;
	int i,j,flag,temp;        
     
    if(deep==3 || deep+count==9){
        return Evaluation();
    }

    if(IsWin()==1){//max必胜
        value=10000;
        return 0;
    }

    if(MAX)//max为true，当前为max节点                  
        flag=10000;
    else//当前为min节点 
        flag=-10000;
        
    for(i=0; i<3 && !prune; i++){
        for(j=0;j<3 && !prune;j++){
            if(chess[i][j]==0){
                if(MAX){//为max节点
                    chess[i][j]=-1;

                    if(IsWin()==-1)//玩家胜利 
                        temp=-10000;
                    else
                        temp=AlphaBeta(flag,deep+1,!MAX);

                    if(temp<flag) flag=temp;//beta节点            
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
    
    if(MAX){//当前为max节点
        if(flag>value)//更新alpha值 
            value=flag;
    }
    else{//当前为min节点
        if(flag<value)//更新beta值 
            value=flag;
    }

    return flag;
}

void PlayerInput()//玩家下棋 
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

	if(temp==1){ //玩家先下 
		while(true){
			PlayerInput();
			//gotoxy(0, 0);
			PrintChess();
			count++;
			Evaluation();
			
			if(y==0){//玩家已经没有了可以获胜的局面了  
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
			if (IsWin()==-1){//玩家获胜 
				printf("\nCongratulations,you win!\n");
				return 0;
			}

			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(chess[i][j]==0){
						chess[i][j]=1;//假设算法放置棋子在这位置 
						AlphaBeta(value,deep,1);//递归进行α-β剪枝 

						if(IsWin()==1){//算法放置棋子在这位置能使自身获胜 
						//	gotoxy(0, 0);
							printf("\nComputer put it at:%d %d\n",i+1,j+1);
							PrintChess();
							printf("\nOh,the computer win!\n");
							return 0;
						}

						if(value>m){//更新m（alpha） 
							m=value;
							row=i;//当前最有解 
							col=j;//当前最有解
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
	else{//算法先下
		while(true){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(chess[i][j]==0){
						chess[i][j]=1;
						AlphaBeta(value,deep,1);//max节点 

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
			
			if(x==0){//死局 
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
//	HideCursor();//可在数据初始化部分调用
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
