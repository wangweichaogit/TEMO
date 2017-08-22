#ifndef _WAIT_GROUP_H_
#define _WAIT_GROUP_H_

#include <condition_variable>
#include <atomic>
#include <assert.h>

namespace TEMO{
class WaitGroup
{
	public:
		using MutexLockGuard = std::lock_guard<std::mutex>;
		WaitGroup (){}
		WaitGroup &operator=(const WaitGroup &) = delete;
		WaitGroup(const WaitGroup &) = delete;
		
		void Add(uint8_t count){
					MutexLockGuard lock(mutex_);
					count_ += count;
			}
		void Done(){
				MutexLockGuard lock(mutex_);
				count_--;
				assert(count_>=0);
				if (count_ == 0){	
					done_.notify_all();
				}
			}
		void Wait(){
				std::unique_lock<std::mutex> lock(mutex_);
				while(count_ >0){
					done_.wait(lock);
				}
			}
	private:
		std::mutex mutex_;
	  int count_{0};
		std::condition_variable done_;
};

}
#endif
