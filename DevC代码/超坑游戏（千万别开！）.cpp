#include <iostream>
#include <ctime>
#include <cstdlib> 
using namespace std;
class a
{
	private:
		long long *p;
	public:
		void e()
		{
			long long i; 
			for(i=1;i<=1000;i++)
			{
				p=new long long; 
			}
		}
};
int main()
{
	a b; 
	int i,n,a;
	for(;;)
	{
		cout<<"�_�°�(1-100)"<<endl;
		srand(time(0)); 
		a=rand()%100+1;
		for(i=0;i<=100;i++)
		{
			    cin>>n;
				if(n<a)
				{
					cout<<"������"<<endl;
				}
				else if(n>a)
				{
					cout<<"������"<<endl; 
				}
				else if(n==a)
				{
					cout<<"������"<<endl; 
					i=100; 
				}
				b.e();
        }
         for(;;)
		 { 
		  cout<<"�Ƿ��ف� �ǣ�1����2"<<endl;
		  b.e();
		  cin>>n;
		  if (n==2)
		  {
		  	return 0;
	      }
		  else if(n==1) break;
		  else if(n>2) cout<<"�ن���һ�飺"; 
		 } 
    }
	return 0;
}
