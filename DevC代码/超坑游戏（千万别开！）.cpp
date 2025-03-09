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
		cout<<"開猜吧(1-100)"<<endl;
		srand(time(0)); 
		a=rand()%100+1;
		for(i=0;i<=100;i++)
		{
			    cin>>n;
				if(n<a)
				{
					cout<<"少啦！"<<endl;
				}
				else if(n>a)
				{
					cout<<"多啦！"<<endl; 
				}
				else if(n==a)
				{
					cout<<"對啦！"<<endl; 
					i=100; 
				}
				b.e();
        }
         for(;;)
		 { 
		  cout<<"是否再來 是：1，否：2"<<endl;
		  b.e();
		  cin>>n;
		  if (n==2)
		  {
		  	return 0;
	      }
		  else if(n==1) break;
		  else if(n>2) cout<<"再問你一遍："; 
		 } 
    }
	return 0;
}
