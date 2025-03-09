#include <windows.h>
#include <iostream>
using namespace std;
const int UNIT = 500;
int m[100]={3,3,3,3,3,3,3,5,1,2,3,4,4,4,3,3,3,2,2,2,1,2,5,3,3,3,3,3,3,3,5,1,2,3,4,4,4,3,3,3,5,5,4,2,1};
int t[100]={1,1,2,1,1,2,1,1,1,1,4,1,1,2,1,1,2,1,1,1,1,2,2,1,1,2,1,1,2,1,1,1,1,4,1,1,2,1,1,2,1,1,1,1,4};
string w[100]={"叮","叮","当，","叮","叮","当，","铃","儿","响","叮","当，","我","们","滑雪","多","快","乐，我们","坐","在","雪","橇","上","哦！","叮","叮","当，","叮","叮","当，","铃","儿","响","叮","当，","我","们","滑雪","多","快","乐，我们","飞","奔","向","前","方！"}; 
void beep_out(int, int);
int main(){		
	cout<<"下面请欣赏《铃儿响叮当》\n";
	int i=0;
	while(t[i]){
		cout<<w[i];
		beep_out(m[i],t[i]);		
		i++;
	}
	cout<<"\n圣诞快乐！";
	return 0;
}
void beep_out(int n, int tn){
	int fn;
	if(n==1) fn=554;
	else if(n==2) fn=622;
	else if(n==3) fn=682;
	else if(n==4) fn=740;
	else if(n==5) fn=831;
	else if(n==6) fn=932;
	else if(n==7) fn=1046;
	else fn=0;
	Beep(fn,UNIT*tn);
	
}
void entry_melody(){
	int a,i=0;
	while(cin>>a){
		m[i++]=a;
	}
}
void entry_time(){
	int a,i=0;
	while(cin>>a){
		t[i++]=a;
	}
}
