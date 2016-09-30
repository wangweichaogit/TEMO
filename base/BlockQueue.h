#ifndef _TEMO_BLOCK_QUEUE_H_
#define _TEMO_BLOCK_QUEUE_H_

#include <queue>
#include <assert.h>
#include "Condition2.h"
#include "Noncopyable.h"

namespace TEMO
{
	template <typename T>
	class BlockQueue:public noncopyable
	{
		public:
			BlockQueue():_mutex(),_cond(_mutex),_queue()
			{
			}
			~BlockQueue() 
			{
			}
			void Put(const T &x)
			{
				SingleMutex s(_mutex);
				_queue.push(x);
				_cond.Notify();
			}
			T Take()
			{
				SingleMutex s(_mutex);
				//���Ϊ�վ������ȴ�,�˴���while��ֹ�ź��жϵȴ�
				while(_queue.empty())
				{
					_cond.Wait();
				}
				//���򵯳�
				T front(_queue.front());
				_queue.pop();
				return front;
			}

			size_t size() const
			{
				SingleMutex s(_mutex);
				return  _queue.size();
			}
		private:
			mutable Mutex _mutex;
			Condition  _cond;
			std::queue<T> _queue;
	};
}

#endif