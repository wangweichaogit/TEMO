#include "ThreadLocal.h"
#include <iostream>
#include <thread>
using namespace std;

using namespace TEMO;
class test
{
	public:
		test():name_("a")
			{
				cout<<"obj create,name = "<<name_<<endl;
			}
		
		~test()
		{
			cout<<"obj delete,name = "<<name_<<endl;
		}
		string name_;		
};

class test2
{
	public:
		test2(string name):name_(name)
			{
				cout<<"obj create,name = "<<name_<<endl;
			}
		
		~test2()
		{
			cout<<"obj delete,name = "<<name_<<endl;
		}
		string name_;		
};
	ThreadLocal<test> local1;
	//ThreadLocal<test> local2;


void thread2()
{
	local1.get().name_="thread11";
	cout<<local1.get().name_<<endl;
	

}
int main()
{
	thread t(thread2);
	t.join();
	cout<<"1"<<endl;
	local1.get().name_="11";

	cout<<local1.get().name_<<endl;
	
	return 0;
}


