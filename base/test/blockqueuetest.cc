#include "BlockingQueue.h"
#include <iostream>
#include <thread>
using namespace std;
using namespace TEMO;

int main()
{
	BlockingQueue<int> queue;
	
	thread tr([&]{
			//int pid = getpid();
			while(1)
			{
				int t = 	queue.take();
				cout<<"thread:"<<t<<endl;
			}
		});
	
	int in;
	while(1)
	{
		cin>>in;
		queue.put(in);
	}
	
	tr.join();

	return 0;
}