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
		cout<<"�x�Ĕ���"<<endl;
		cout<<"Ո������7�����У��xһ���Kӛ�����Y��"<<endl;
		cout<<t[0]<<endl;
		system("pause");
		for(i=1;i<=3;i++)
		{
			system("cls");
			cout<<i<<"��������Ĕ����І᣿�У�1���]�У�0"<<endl;
			cout<<t[i]<<endl;
			do
			{
			  cin>>a[i];	
			}while(a[i]<0||a[i]>1); 
		} 
		ans=4*a[3]+2*a[2]+a[1];
		system("cls");
		cout<<"��������Ĕ���:";
		cout<<ans<<endl; 
		 for(;;)
		 { 
		  cout<<"�Ƿ��ف� �ǣ�1����2"<<endl;
		  cin>>n;
		  if (n==2)
		  {
		  return 0;
	      }
		  else if(n==1)
		  { 
		  break;
	      }
		  else if(n>2) cout<<"�ن���һ�飺"; 
		 } 
		 system("cls"); 
    }
	return  0;
}
