#include "../Thread.h"
#include <iostream>
#include <unistd.h>
#include <functional>
using namespace std;
using TEMO::Thread;
	

int bruning=true;
void func1(string str)
{
	while(bruning)
	{
		cout<<str.c_str()<<endl;
		sleep(1);
	}
}
int main()
{
	Thread th1(bind(&func1,"1234"));
	th1.Start();
	getchar();
	bruning = false;
	th1.Join();
	return 0;
}