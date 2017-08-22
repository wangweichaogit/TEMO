#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <string>
#include "WaitGroup.h"
#include "BlockingQueue.h"

using namespace std;
using namespace TEMO;

typedef  std::function<void()> funtor;

void dowork(BlockingQueue<funtor> &funtorlist)
{
	while(1)
	{
		funtor f = std::move(funtorlist.take());
		f();
	}
}

void myprint(WaitGroup &group,int index)
{

	std::this_thread::sleep_for(std::chrono::seconds(index));
	cout<<"invoke:"<<index<<endl;
	group.Done();
}

void test()
{
	BlockingQueue<funtor>  funtorlist;
	WaitGroup              group;

	thread t(dowork,std::ref(funtorlist));

	t.detach();

	for (int i=0;i<10;i++){
		group.Add(1);
		funtorlist.put(std::bind(myprint,std::ref(group),i));
	}
	group.Wait();	
	cout<<"done"<<endl;
}
int main()
{
	test();
	return 0;
}
