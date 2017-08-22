#ifndef _THREAD_LOCAL_H_
#define _THREAD_LOCAL_H_

// thread local 保存线程本地存储
#include <pthread.h>
#include <functional>
#include <assert.h>

namespace TEMO
{

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       assert(errnum == 0); (void) errnum;})

template<typename T>
class ThreadLocal
{
public:
	ThreadLocal()
	{
		MCHECK(pthread_key_create(&key_,&ThreadLocal::Destructor));
	}
	~ThreadLocal()
	{
		MCHECK(pthread_key_delete(key_));
	}
	ThreadLocal(ThreadLocal &&) = default;
	ThreadLocal &operator=(ThreadLocal &&) = default;
	
	T &get()
	{
		T* perThreadValue = static_cast<T*>(pthread_getspecific(key_));
    if (!perThreadValue)
    {
      T* newObj = new T();
     	MCHECK(pthread_setspecific(key_, newObj));
      perThreadValue = newObj;
    }
    return *perThreadValue;
	}
private:
	ThreadLocal(const ThreadLocal &) = delete;
	ThreadLocal &operator=(const ThreadLocal&) = delete;
	
	static inline void Destructor(void  *x)
	{
		T *obj = static_cast<T *>(x);
		//对完整类型析构
		typedef char type_must_be_complete[sizeof(T)?1:-1];
		(void) sizeof(type_must_be_complete);
		delete obj;
	}
private:
	pthread_key_t  key_;
};

}


#endif