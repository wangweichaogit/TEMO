/*
条件变量,再用到条件变量的地方,几乎都会用到mutex，因此将mutex作为引用传递进去
这样在wait的时候，外部mutex要先加锁

使用场景几乎只有一种
1.先加锁，保护判断表达式的读写
2.mutex加锁的时候才能够调用wait
3.将判断条件和wait放入while循环（信号打断wait后可以再次检测一次）
*/
#ifndef _TEMO_CONDITION2_H_
#define _TEMO_CONDITION2_H_

#include "Mutex.h"
#include <time.h>

namespace TEMO
{
	class Condition:public noncopyable
	{
		public:
			Condition(Mutex &mutex):_mutex(mutex)
			{
				 pthread_cond_init(&_cond,NULL);
			}
			~Condition() { pthread_cond_destroy(&_cond);}
			
			void Wait() 
			{ 
				pthread_cond_wait(&_cond,_mutex.GetMutex());
			}
			bool Wait(int nTimeout) 
			{

        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        int timeoutSec = nTimeout/1000;
        int timeoutMilliSec = nTimeout%1000;
        ts.tv_sec += timeoutSec;
        int tsMilliSec = ts.tv_nsec/1000/1000; 
        if ( tsMilliSec + timeoutMilliSec < 1000 )
        {
            ts.tv_nsec = ts.tv_nsec + timeoutMilliSec*1000*1000;
        }
        else
        {
            ts.tv_sec += 1;
            ts.tv_nsec =  (tsMilliSec + timeoutMilliSec -1000)*1000*1000;		
        }	
				return (0 == pthread_cond_timedwait(&_cond, _mutex.GetMutex(), &ts));
			}

			void Notify() 
			{
				pthread_cond_signal(&_cond);
			}
			void NotifyAll()
			{
				pthread_cond_broadcast(&_cond);
			}
		private:
			Mutex &_mutex;
			pthread_cond_t _cond;
	};
}

#endif  // _TEMO_CONDITON_H_