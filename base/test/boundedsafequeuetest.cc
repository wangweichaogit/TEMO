#include "../BounedBlockQueue.h"
#include "../Thread.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;
TEMO::BounedBlockQueue<string> bqstring(20) ;

void pprint()
{
	bool running=true;
	while(running)
	{
		string ret = bqstring.Take();
		printf("thread pop ret:%s\n",ret.c_str());
		running = (ret!="quit");
	}
	printf("thread end\n");
}
int main()
{
	
	TEMO::Thread th1(bind(pprint));
	th1.Start();
	
	char buf[100];
	bool running=true;
	while(running)
	{
		memset(buf,0,sizeof(buf));
		cin>>buf;
		running =(0!= strcmp(buf,"quit"));
		bqstring.Put(buf);
	}
	th1.Join();
	return 0;
}