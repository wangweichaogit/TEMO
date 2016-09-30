#include <stdio.h>
#include <iostream>
#include "../Condition.h"
using namespace std;
int main()
{
	TEMO::Condition c;
	//c.Set();
	c.Wait(10000);
	//cout<<"111"<<endl;
	
	//pthread_mutex_t mutex;
	//pthread_cond_t cond;
	//pthread_mutex_init(&mutex,0);
	//
	//pthread_cond_init(&cond,0);
	//pthread_mutex_lock(&mutex);
	//pthread_cond_wait(&cond,&mutex);
	return 0;
}