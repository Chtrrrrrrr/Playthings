#include<iostream>
#include<cstdio>
#include<conio.h>
#include<cstdlib>
#include<windows.h> 
using namespace std;
const int N=30;
bool mouse=0;
char map[N][N]=
{
	"#########American#######",	
	"#   #^   ^ ^^ ^^   ^   #",	
	"# #^#  ## ^##^ ^## ##  #",	
	"#     ^##  ##   ##    ##",	
	"## #   ## #########  ###",	
	"# ^  # ##    ^  ##   ###",	
	"#    # ###     ### ^ ###",	
	"#   #^ #   ^^  ###   ###",	
	"#   ## #   ## ^    # ###",	
	"#          ##    ##  ^##",	
	"## ## ## ###############",
	"## ## ##    ^^## @  ####",
	"##   ^ # ##      #  ####",
	"########################",	
};
struct Point
{
	int row;
	int col;
	int step;
	int fid;	
};
Point q[N*N];
bool bk[N][N];
int head;
int tail;
int d[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
void prt();
void bfs();
void push(int,int,int,int);
void pausing();
void set_path(Point);
int main()
{
	prt();
	int r0;
	int c0;
	cout<<"请确认病毒在美国的哪？";
	for(;cin>>r0>>c0,map[r0][c0]!=' ';)
	{
		int oi;
		cout<<"if you take the sare to there it will die do you will ?(1/0)?"<<endl;
		cin>>oi;
		if(oi)
		{
			cout<<"the people is die";
			return 0;
		}
	}
	push(r0,c0,0,0);
	map[r0][c0]='*';
	bfs();	
	return 0;
}
void push(int r,int c,int s,int id)
{
	Point p={r,c,s,id};
	q[++tail]=p;
	bk[r][c]=1;
	if(map[r][c]==' ') map[r][c]='0'+s%10;
}
void prt()
{
	for(int r=0;map[r][0];cout<<endl,r++)
	{
		for(int j=0;map[r][j];j++)
		{
			putchar(map[r][j]);
		}
	}
}
void pausing()
{
	Sleep(30);
	system("cls");
}
void bfs()
{
	while(head!=tail)
	{
		for(int r,c,s,i=0;i<=4 ;i++)
		{
			r=q[head+1].row+d[i][0];
			c=q[head+1].col+d[i][1];	
			s=q[head+1].step+1;		
			if(r<0||c<0)  continue;
			if(map[r][c]=='@')
			{
				set_path(q[head+1]);
				prt(); 
				return;
			}
			if(map[r][c]==' '&&bk[r][c]==0)
			{
				//set_path(q[head+1]);
				push(r,c,s,head+1);
				prt();
				pausing();
			} 
			if(map[r][c]=='^')
			{
				//set_path(q[head+1]);	
				map[r][c]='~';
				push(r,c,s,head+1);
				prt();
				pausing(); 
			} 
		}	
		head++;	
	}
	cout<<"the people is healthy(safety)";
} 
void set_path(Point p)
{
	int r=p.row;
	int c=p.col;
	int s=p.step;
	int id=p.fid;
	if(id==0)	
	{
		return ;
	}
	map[r][c]='!';
	cout<<"map["<<r<<"]["<<c<<"]\n";
	set_path(q[id]);
}





