/*---ͷ�ļ�---*/
//#include<all the include.h>
#include<conio.h>//getch()���ڿ�
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<string.h>
#include<iostream>
using namespace std;
/*-------Ԥ��������----------*/
#define Up 1
#define Down 2
#define Left 3
#define Right 4
/*-------��������---------*/
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
/*-----��������---------*/
//int direct(char );//��ȡ����
void move(int );//�ƶ�
void goto_xy(int x, int y);//��궨λ
void prt();//��ӡ��ͼ     
//-3272-3280-3275-3277
/*-------------------main------------------*/
int main()
{
	
	/*int h;
	int w;
	srand(time(0));
	a=rand()%i+1;
	*///�漴����

	for(int j=1;j<=100;j++)
	{
		if(j==1)//------�ȴ�ӡһ��------
		{
			/*-----��ӡ��ͼ--------*/ 
			prt();//prt���� 
			goto_xy(x,y);
			cout<<"   (^_^)   "<<endl;
			goto_xy(x,y+1);
			cout<<"    \|/  "<<endl;
			goto_xy(x,y+1);
			cout<<"    |.|."<<endl;
		}
		/*----��ȡ����------*/
		while(!kbhit())//��û�м�����
		{
			move(4);//ǰ��
			Sleep(1000); //��ʱ 
		}
		char ch;
		ch=getch();
		if(ch==-32)//�� 
		{
			move(1);//�����ƶ� 
		}
	}
    return 0;
}
/*----------------------����---------------------*/
void goto_xy(int x, int y)//��궨λ
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

/*int direct(char ch){
	if(ch==-32){	//���Ǵ����������Ҽ�ͷ��
		ch=getch();
		if(ch==72) ch='w';
		else if(ch==80) ch='s';
		else if(ch==75) ch='a';
		else if(ch==77) ch='d';
	}
	if(ch>='A'&&ch<='Z') ch+=32;//��дתСд
	if(ch=='w') return Up;
	if(ch=='a') return Left;
	if(ch=='d') return Right;
	if(ch=='s') return Down;
	return 0;
}
*/
void move(int j)//�ƶ�����
{
	for(int i=1;i<=3;i++)
	{
		/*����*/ 
		system("cls");
		/*----�ȴ�ӡһ�µ�ͼ------*/
		prt();
		/*�жϷ���*/ 
		if(j==3)
		{
			x--;//��
		}
		if(j==4)
		{
			x++;//��
		}
		if(j==1)
		{
			y--;//��
		}
		if(j==2)
		{
			y++;//��
		}
		/*��ʾ����*/
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
