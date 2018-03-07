#include "ThreadSafeQueue.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
using namespace std;

int main(int argc,const char *argv[])
{
	if (argc != 4)
	{
		printf("useage %s count inthreadnumber outthreadnumber\n",argv[0]);	
		return -1;
	}
	
	unsigned long long number = std::atol(argv[1]);
	unsigned int innumber= std::atoi(argv[2]);
	unsigned int outnumber = std::atoi(argv[3]);
	printf("%lld %d %d\n",number,innumber,outnumber);
	std::vector<std::thread> inthreads;
	std::vector<std::thread> outthreads;

	ThreadSafeQueue<int> queue;
	std::chrono::time_point<std::chrono::system_clock> time1=std::chrono::system_clock::now();	
	
	for(int i =0;i <outnumber;i++)
	{
		outthreads.push_back(std::thread([&]{
			int t;	
			while(1)
			{
				queue.pop(t);	
				if(t==0)
				{
					printf("end\n");					
					std::chrono::time_point<std::chrono::system_clock> time2=std::chrono::system_clock::now();	
					cout<<std::chrono::duration_cast<std::chrono::milliseconds>(time2-time1).count()<<"ms"<<endl;
				}
			}
		}));
	}
	std::mutex mu;
	for(int i=0;i<innumber;i++)
	{
		inthreads.push_back(std::thread([&]{
	while(1)
	{
		unsigned long long i=0;
		{
		  std::lock_guard<std::mutex> lock(mu);
		  if(number==0)
			{
			printf("end in\n");
			break;
			}
		  i = --number; 
		}
		queue.push(i);
	}
//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}));
	}

	
	getchar();
	return 0;
}
