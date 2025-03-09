/*---头文件---*/
//#include<all the include.h>
#include<conio.h>//getch()所在库
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<string.h>
#include<iostream>
using namespace std;
/*-------预处理命令----------*/
#define Up 1
#define Down 2
#define Left 3
#define Right 4
/*-------变量声明---------*/
//char u;
int y=7,x=0;
char ch;
int d;
char map[10][20]=
{
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ','@ ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
};
/*-----声明定义---------*/
//int direct(char );//获取方向
void move(int );//移动
void goto_xy(int x, int y);//光标定位
void prt();//打印地图     
//-3272-3280-3275-3277
/*-------------------main------------------*/
int main()
{
	
	/*int h;
	int w;
	srand(time(0));
	a=rand()%i+1;
	*///随即方块

	for(int j=1;j<=100;j++)
	{
		if(j==1)//------先打印一遍------
		{
			/*-----打印地图--------*/ 
			prt();//prt函数 
			goto_xy(x,y);
			cout<<"   (^_^)   "<<endl;
			goto_xy(x,y+1);
			cout<<"    \|/  "<<endl;
			goto_xy(x,y+1);
			cout<<"    |.|."<<endl;
		}
		/*----获取方向------*/
		while(!kbhit())//当没有键按下
		{
			move(4);//前进
			Sleep(1000); //延时 
		}
		char ch;
		ch=getch();
		if(ch==-32)//上 
		{
			move(1);//向下移动 
		}
	}
    return 0;
}
/*----------------------定义---------------------*/
void goto_xy(int x, int y)//光标定位
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

/*int direct(char ch){
	if(ch==-32){	//剥壳处理上下左右箭头键
		ch=getch();
		if(ch==72) ch='w';
		else if(ch==80) ch='s';
		else if(ch==75) ch='a';
		else if(ch==77) ch='d';
	}
	if(ch>='A'&&ch<='Z') ch+=32;//大写转小写
	if(ch=='w') return Up;
	if(ch=='a') return Left;
	if(ch=='d') return Right;
	if(ch=='s') return Down;
	return 0;
}
*/
void move(int j)//移动函数
{
	for(int i=1;i<=3;i++)
	{
		/*清屏*/ 
		system("cls");
		/*----先打印一下地图------*/
		prt();
		/*判断方向*/ 
		if(j==3)
		{
			x--;//左
		}
		if(j==4)
		{
			x++;//右
		}
		if(j==1)
		{
			y--;//上
		}
		if(j==2)
		{
			y++;//下
		}
		/*显示部分*/
		goto_xy(x,y);
		cout<<"   (^_^)   "<<endl;
		goto_xy(x,y+1);
		cout<<"    \|/  "<<endl;
		goto_xy(x,y+1);
		cout<<"    |.|."<<endl;
	}
}
void prt()
{
	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=19;j++)
		{
			cout<<map[i][j];
		}
		cout<<endl; 
	}	
} 
