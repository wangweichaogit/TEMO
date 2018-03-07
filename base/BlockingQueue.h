#ifndef _BLOCKINGQUEUE_H_
#define _BLOCKINGQUEUE_H_

#include <mutex>
#include <condition_variable>
#include <deque>
#include <assert.h>


template <typename T>
class BlockingQueue
{
	public:
		using MutexLockGuard = std::lock_guard<std::mutex>;
		
		BlockingQueue():mutex_(),notEmpty_(),queue_() {}
		BlockingQueue(const BlockingQueue &queue) = delete;
		BlockingQueue & operator=(BlockingQueue &queue) = delete;
		
		void put(T t)
		{
			MutexLockGuard lock(mutex_);
			queue_.push_back(std::move(t));
			notEmpty_.notify_one();
		}
		
		T take()
		{
			std::unique_lock<std::mutex> lock(mutex_);
			
			notEmpty_.wait(lock,[this]{
				return !this->queue_.empty();
			});
			
			assert(!queue_.empty());

			T front(std::move(queue_.front()));
			queue_.pop_front();
			return front;
		}

		size_t size() const
		{
			MutexLockGuard lock(mutex_);
			return queue_.size();
		}
	private:
		mutable std::mutex mutex_;
		std::condition_variable notEmpty_;
		std::deque<T> queue_;
};
#endif
