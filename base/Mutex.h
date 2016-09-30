
#ifndef _TEMO_MUTEX_H_
#define _TEMO_MUTEX_H_

#include <pthread.h>
#include "Noncopyable.h"

namespace TEMO
{

class Mutex: public noncopyable
{
public:
	Mutex() {pthread_mutex_init(&_mutex,NULL);}
	virtual ~Mutex() {pthread_mutex_destroy(&_mutex);}
	void Lock()  {pthread_mutex_lock(&_mutex);}
	void Unlock() {pthread_mutex_unlock(&_mutex);}
	bool TryLock() {return pthread_mutex_trylock(&_mutex)==0;}
	pthread_mutex_t *GetMutex() {return &_mutex;}
private:
	pthread_mutex_t _mutex;
};

class SingleMutex:public noncopyable
{
public:
	SingleMutex(Mutex &mtx):_mutex(mtx) {_mutex.Lock();}
	~SingleMutex() {_mutex.Unlock();}
private:
	Mutex &_mutex;
};
	
}

#endif