#ifndef _THREADSAFE_QUEUE_H_
#define _THREADSAFE_QUEUE_H_

#include <mutex>
#include <atomic>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue
{
private:
	using MutexLockGuard = std::lock_guard<std::mutex>;
    struct node
    {
        T* data;
	node* next;
    };
	std::mutex head_mutex;
	node* head;
	std::mutex tail_mutex;
	node* tail;
	std::condition_variable data_cond;
public:
	ThreadSafeQueue() :head(new node), tail(head){}
	ThreadSafeQueue(const ThreadSafeQueue & other) = delete;
	ThreadSafeQueue& operator=(const ThreadSafeQueue & other) = delete;

	bool try_pop(T &value);
	void pop(T &value);
	void push(T value);
private:
	node * get_tail()
	{
		MutexLockGuard tail_lock(tail_mutex);
		return tail;
	}

	node* try_pop_head(T &value)
	{
		MutexLockGuard head_lock(head_mutex);
		if (head == get_tail())
		{
			return nullptr;
		}
		value = std::move(*head->data);
		node* old_head = head;
		head = old_head->next;
		return old_head;
	}
};

template<typename T>
void ThreadSafeQueue<T>::push(T value)
{
	T* new_date = new T(std::move(value));
	node *p= new node;
	{
		MutexLockGuard tail_lock(tail_mutex);
		tail->data = new_date;
		node * new_tail = p;
		tail->next = p;
		tail = new_tail;
	}
	data_cond.notify_one();
}

template<typename T>
void ThreadSafeQueue<T>::pop(T &value)
{
	std::unique_lock<std::mutex> head_lock(head_mutex);
	data_cond.wait(head_lock, [&]{
		return head != get_tail();
	});

	value = std::move(*head->data);
	node* old_head = head;
	head = old_head->next;
}

template<typename T>
bool ThreadSafeQueue<T>::try_pop(T &value)
{
	std::unique_ptr<node> old_head = try_pop_head(value);
	return old_head == nullptr ? false : true;
}


#endif
