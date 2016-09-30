/*
int类型的院子操作，加 减等，
*/

#ifndef _TEMO_ATOMIC_H_
#define _TEMO_ATOMIC_H_

#include <stdint.h>

namespace TEMO
{
	template <typename T>
	class AtomicInteger
	{
		public:
			AtomicInteger():_value(0) {}
			virtual ~AtomicInteger() {}
	
			//获取值
			T get();
			//获取旧值，赋予新值
			T getAndSet(T val);
			
			//++T
			T increment();
			//--T
			T decrement();
			
			// return _value+val
			T addAndGet(T val);
			// return _value
			T getAndAdd(T val);
		private:
			//放置编译器优化
			volatile T  _value;
	};

template <typename T>
T AtomicInteger<T>::get() 
{
	//原子操作
	return __sync_val_compare_and_swap(&_value, 0, 0);
}

template <typename T>
T AtomicInteger<T>::getAndSet(T val)
{
	return __sync_lock_test_and_set(&_value,val);
}

template <typename T>
T AtomicInteger<T>::increment()
{
	return __sync_fetch_and_add(&_value, 1) +1;
}

template <typename T>
T AtomicInteger<T>::decrement()
{
	return __sync_fetch_and_add(&_value, -1) -1;
}
			
template <typename T>
T AtomicInteger<T>::addAndGet(T val)
{
	return __sync_fetch_and_add(&_value, val) + val;
}

template <typename T>
T AtomicInteger<T>::getAndAdd(T val)
{
	return __sync_fetch_and_add(&_value, val);
}

typedef AtomicInteger<int32_t> AtomicInt32;
typedef AtomicInteger<int64_t> AtomicInt64;

}
#endif    // Atomic.h