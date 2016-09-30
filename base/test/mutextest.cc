#include "../Mutex.h"
#include "../Thread.h"
#include <stdio.h>
#include <functional>
#include <unistd.h>
using namespace TEMO;
Mutex mutex;
int gint=0;
int gcount=0;
void func1()
{
	while(1)
	{
		SingleMutex s(mutex);
		if (gcount>=10000)
			break;
		printf("thread1::gint%d\n",gcount);
		gcount++;
		//sleep(1);
	}
}

void func2()
{
	while(1)
	{
		SingleMutex s(mutex);
		if (gcount>=10000)
			break;
		printf("thread2::gint%d\n",gcount);
		gcount++;
		//sleep(1);
	}
}
int main()
{
	TEMO::Thread th1(std::bind(func1));		
	TEMO::Thread th2(std::bind(func2));
		
	th1.Start();
	th2.Start();
	th1.Join();
	th2.Join();
	return 0;
}