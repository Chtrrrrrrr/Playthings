#include <iostream>
#include<cstdlib>
#include<string>
using namespace std;

int main()
{
	int n;
	for(;;)
	{
		int i,a[4],ans;
		string t[4];
		t[0]="1,2,3,4,5,6,7";
		t[1]="1,3,5,7";
		t[2]="2,3,6,7";
		t[3]="4,5,6,7";
		cout<<"讀心數："<<endl;
		cout<<"請從下面7個數中，選一個並記在心裏。"<<endl;
		cout<<t[0]<<endl;
		system("pause");
		for(i=1;i<=3;i++)
		{
			system("cls");
			cout<<i<<"問：下面的數中有嗎？有：1，沒有：0"<<endl;
			cout<<t[i]<<endl;
			do
			{
			  cin>>a[i];	
			}while(a[i]<0||a[i]>1); 
		} 
		ans=4*a[3]+2*a[2]+a[1];
		system("cls");
		cout<<"你心中想的數是:";
		cout<<ans<<endl; 
		 for(;;)
		 { 
		  cout<<"是否再來 是：1，否：2"<<endl;
		  cin>>n;
		  if (n==2)
		  {
		  return 0;
	      }
		  else if(n==1)
		  { 
		  break;
	      }
		  else if(n>2) cout<<"再問你一遍："; 
		 } 
		 system("cls"); 
    }
	return  0;
}
