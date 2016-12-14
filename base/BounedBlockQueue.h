/*
带边界的阻塞队列
*/

#ifndef _TEMO_BOUNEDBLOCKQUEUE_H_
#define _TEMO_BOUNEDBLOCKQUEUE_H_

#include "Noncopyable.h"
#include "Condition2.h"
#include <queue>

namespace TEMO
{
		template<typename T>
		class BounedBlockQueue :public noncopyable
		{
			public:
				BounedBlockQueue(int maxSize):_mutex(),_notEmpty(_mutex),_notFull(_mutex),_maxSize(maxSize) {}
				void Put(const T & t)
				{
					SingleMutex s(_mutex);
					while(_queue.size() >= _maxSize)
					{
						_notFull.Wait();
					}
					_queue.push(t);
					_notEmpty.Notify();
				}
				
				T Take()
				{
					SingleMutex s(_mutex);
					while(_queue.empty())
					{
						_notEmpty.Wait();
					}
					T front = _queue.front();
					_queue.pop();
					_notFull.Notify();
					return front;
				}
				
			 bool Empty() const
		  {
		   SingleMutex s(_mutex);
		    return _queue.empty();
		  }
		
		  bool Full() const
		  {
		    SingleMutex s(_mutex);
		    return _queue.size() >= _maxSize;
		  }
		
		  size_t Size() const
		  {
		    SingleMutex s(_mutex);
		    return _queue.size();
		  }
			private:
				mutable Mutex _mutex;
				Condition     _notEmpty;
				Condition     _notFull;
				unsigned int  _maxSize;
				std::queue<T> _queue;
		};
}
#endif  // BounedBlockQueue.h