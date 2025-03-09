#include<iostream>
#include<windows.h>
#include<cstdio>
#include<string.h>
using namespace std;

int main()
{
	int y=0;
	char daan[10];
	char a[5][10]={{'i','n','t'},{'f','l','o','a','t'},{'c','h','a','r'},{'b','o','o','l'},{'s','t','r','i','n','g'}};
	char b[5][10]={{'d','o'},{'i','f'},{'e','l','s','e'},{'c','l','a','s','s'},{'f','r', 'e','n','d'}};
	char c[5][10]={{'b','r','e','a','k'},{'m','a','i','n'},{'r','e','t','u','r','n'},{'u','s','i','n','g'},{'n','a','m','e','s','p','a','c','e'}};
	char d[5][10]={{'s','t','d',},{'#','i','n','c','l','u','d','e'},{'#','d','f','i','n','e'}};
	cout<<"欢迎使用C,C++关键字练习程序！"<<endl<<endl<<endl<<endl;
	cout<<"              取消：2  继续：1"<<endl<<endl;
	int jixu=0;
	cin>>jixu;
	system("cls");
	if(jixu==1)
	{
		cout<<"准备好了吗？";
		Sleep(3000);
		system("cls");
		cout<<"开始：1"<<endl;
		int key=0;
		cin>>key;
		system("cls");
		if(key==1)
		{
			for(int i=3;i>=0;i--)
			{
				cout<<i;
				Sleep(1000);
				system("cls");
			}
			cout<<"开始！";
			Sleep(1000);
			system("cls");
			for(int j=0;j<=4;j++)
			{
				if(y==1)
				{
					j--;
					y--;
				}
				for(int i=0;a[j][i];i++)
				{
					cout<<a[j][i];
				}
				cout<<endl;
				gets(daan);
				if(strcmp(daan,a[j])) ;
				else if(j==0) y=1;
				else j--;
			}
			for(int j=0;j<=4;j++)
			{
				for(int i=0;a[j][i];i++)
				{
					cout<<a[j][i];
				}
				cout<<endl;
				gets(daan);
				if(strcmp(daan,a[j])) ;
				else j--;
			}
			for(int j=0;j<=4;j++)
			{
				for(int i=0;a[j][i];i++)
				{
					cout<<a[j][i];
				}
				cout<<endl;
				gets(daan);
				if(strcmp(daan,a[j])) ;
				else j--;
			}
			for(int j=0;j<=4;j++)
			{
				for(int i=0;a[j][i];i++)
				{
					cout<<a[j][i];
				}
				cout<<endl;
				gets(daan);
				if(strcmp(daan,a[j])) ;
				else j--;
			}
		}
	}
	if(jixu==2)
	  return 0;
	return 0;
}
