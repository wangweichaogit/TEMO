/*
条件变量
*/
#ifndef _TEMO_CONDITION_H_
#define _TEMO_CONDITION_H_

#include "Mutex.h"
#include <time.h>

namespace TEMO
{
	class Condition:public noncopyable
	{
		public:
			Condition() { pthread_cond_init(&_cond,NULL);}
			~Condition() { pthread_cond_destroy(&_cond);}
			void Wait() 
			{ 
				SingleMutex s(_mutex);
				pthread_cond_wait(&_cond,_mutex.GetMutex());
			}
			/*block for ms
			* return true：timeout false：get signal
			*/
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
        SingleMutex s(_mutex);
				return (0 == pthread_cond_timedwait(&_cond, _mutex.GetMutex(), &ts));
			}
			void Set() 
			{
				pthread_cond_signal(&_cond);
			}
		private:
			Mutex _mutex;
			pthread_cond_t _cond;
	};
}

#endif  // _TEMO_CONDITON_H_