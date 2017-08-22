#ifndef _THREAD_LOCAL_SINGLETON_H_
#define _THREAD_LOCAL_SINGLETON_H_

// 创建线程
#include <pthread.h>
#include <assert.h>

namespace TEMO
{
template <typename T>
class ThreadLocalSingleton
{
public:
	static T&Instance()
	{
		if (!pValue_)
		{
			pValue_ = new T();
			deleter_.set(pValue_);
		}
		return *pValue_;
	}
	
	static T*Pointer()
	{
		return pValue_;
	}

private:
	ThreadLocalSingleton() = default;
	~ThreadLocalSingleton() = default;
	ThreadLocalSingleton(const ThreadLocalSingleton&) = delete;
	ThreadLocalSingleton& operator=(const ThreadLocalSingleton&) = delete;
	
	static void Destructor(void *obj)
	{
		assert(obj == pValue_);
		//对完整类型析构
		typedef char type_must_be_complete[sizeof(T)?1:-1];
		(void) sizeof(type_must_be_complete);
		delete pValue_;
		pValue_ = nullptr;
	}
	
	class Deleter
	{
		public:
		Deleter()
		{
			pthread_key_create(&key_,&ThreadLocalSingleton::Destructor);
		}
		~Deleter()
		{
			pthread_key_delete(key_);
		}
		void set(T *newObj)
		{
			assert(pthread_getspecific(key_) == nullptr);
			pthread_setspecific(key_,newObj);
		}
		private:
			pthread_key_t key_;
	};
private:
	static  __thread T* pValue_;
	static Deleter      deleter_;
};

template <typename T>
__thread T *ThreadLocalSingleton<T>::pValue_ = nullptr;
	
template <typename T>
typename ThreadLocalSingleton<T>::Deleter ThreadLocalSingleton<T>::deleter_;

}
#endif