/*
int���͵�Ժ�Ӳ������� ���ȣ�
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
	
			//��ȡֵ
			T get();
			//��ȡ��ֵ��������ֵ
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
			//���ñ������Ż�
			volatile T  _value;
	};

template <typename T>
T AtomicInteger<T>::get() 
{
	//ԭ�Ӳ���
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