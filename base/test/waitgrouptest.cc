#include <iostream>
#include <sys/types.h>
#include <chrono>
#include "WaitGroup.h"
#include <thread>
using namespace TEMO;
using namespace std;
/*
void dowork()
{
	cout<<"work"<<endl;
}
void test1()
{
	std::thread t(dowork);	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	t.join();
}
*/

//  发起多个子线程,所有子线程完成工作后,主线程退出

void dowork2(WaitGroup &group,int sleepTime)
{

	std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
	cout<<"done "<<std::this_thread::get_id()<<"  "<<sleepTime<<endl;
	group.Done();
}

void test2()
{
	WaitGroup group;
	for (int i =0;i<10;i++){
		group.Add(1);
		std::thread t(dowork2,std::ref(group),i);
		t.detach();
	}	
	group.Wait();
	cout<<"all done"<<endl;
}

// 发起多个子线程,所有子线程同时工作
void dowork3(WaitGroup &group,int id)
{
	group.Wait();
	cout<<"done "<<std::this_thread::get_id()<<"  "<<id<<endl;
}

void test3()
{
	WaitGroup group;
	for(int i=0;i<10;i++){
		group.Add(1);
		std::thread t(dowork3,std::ref(group),i);
		t.detach();
	}
	cout<<"wait 5s"<<endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	for(int i =0;i<10;i++){
		group.Done();
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
}


int main()
{
	test2();
	test3();
	return 0;
}
