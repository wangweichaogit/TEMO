/*
信号量
*/
#ifndef _TEMO_SEMAPHORE_H_
#define _TEMO_SEMAPHORE_H_

#include "Noncopyable.h"
#include <semaphore.h>
#include <errno.h>
#include <time.h>

namespace TEMO
{
	class Semaphore: public noncopyable
	{
		public:
			Semaphore(int initCount)
			{
				//线程间信号量
				sem_init(&_sem,0,initCount);
			}
			~Semaphore()
			{
				sem_destroy(&_sem);
			}
			void Post()
			{
				sem_post(&_sem);
			}
			bool Wait()
			{
				int ret = 0;
				//当sem_wait阻塞时被信号打断,则继续等待
				//return true：等待到信号量 flase：失败
				while((ret = sem_wait(&_sem)) == -1 && errno == EINTR)
					continue;
				return ret==0;
			}
			// wait at most timeout ms
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
        int ret = 0;
        while ((ret = sem_timedwait(&_sem,&ts))==-1 && errno == EINTR)
        	continue;
        return ret == 0;
			}
		private:
			sem_t _sem;
	};
}

#endif