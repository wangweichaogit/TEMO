#include <iostream>
#include "ThreadLocalSingleton.h"
#include <thread>

using namespace std;
using namespace TEMO;

class test
{
	public:
	test()
	{
		cout<<"ctor threadid:"<<std::this_thread::get_id()<<endl;
	}
	~test()
	{
		cout<<"dtor threadid:"<<std::this_thread::get_id()<<endl;
	}
	void print()
	{
		cout<<"threadid:"<<std::this_thread::get_id()<<"name"<<name<<endl;
	}
	string name;
};

void threadfunc()
{
	ThreadLocalSingleton<test>::Instance().print();
	ThreadLocalSingleton<test>::Instance().name="aa";
	ThreadLocalSingleton<test>::Instance().print();
}


int main()
{
	ThreadLocalSingleton<test>::Instance().name="bb";
		ThreadLocalSingleton<test>::Instance().print();
	std::thread tt(threadfunc);
	tt.join();

	return 0;
}