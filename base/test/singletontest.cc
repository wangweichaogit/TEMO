#include <iostream>
#include <thread>
#include "WaitGroup.h"
#include "Singleton.h"
using namespace std;
using namespace TEMO;

class demo
{
public:
	demo()
	{
		cout<<"ctor:"<<std::this_thread::get_id()<<endl;
	}
	void run()
	{
		cout<<"invoke:"<<std::this_thread::get_id()<<endl;
	}
};


void doCreat(WaitGroup &group)
{
	group.Wait();
	demo &d = Singleton<demo>::Instance();
	d.run();	
}

void dotest()
{
	WaitGroup group;	
	group.Add(1);
	for(int i = 0; i<20;i++){
		thread t(doCreat,std::ref(group));
		t.detach();
	}
	group.Done();
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main()
{
	dotest();
	return 0;
}
