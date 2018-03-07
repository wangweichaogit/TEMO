/*
线程类,使用function bind回调
线程退出的正常方式只有一种，就是线程函数执行完毕，退出
*/
#ifndef _TEMO_THREAD_H_
#define _TEMO_THREAD_H_
#include <pthread.h>
#include <functional>
#include <assert.h>
using std::string;

namespace TEMO
{
class Thread
{
public:
	typedef std::function<void ()> ThreadFunc;
	
	Thread(const Thread::ThreadFunc &func,const string &name=string()):mThreadFunc(func),mThreadId(0),mBStarted(false),mBjoined(false),mName(name) {}
	~Thread()
	{
		if (mBStarted && !mBjoined)
		{
			pthread_detach(mThreadId);		
		}
	}
	void Start();
	int  Join();
	
	bool Started() const { return mBStarted;}
	const string &Name() const { return mName;}
private:
	static void* RunInThread(void *obj);
	Thread(const Thread&) = delete;
	Thread& operator=(const Thread&) = delete;
private:
	ThreadFunc mThreadFunc;
	string     mName;
	pthread_t  mThreadId;
	bool       mBStarted;
	bool       mBjoined;
};

void Thread::Start()
{
	mBStarted = true;
	if (pthread_create(&mThreadId,NULL,&Thread::RunInThread,this))
	{
		mBStarted = false;
	}
}
int Thread::Join()
{
	assert(mBStarted);
	assert(!mBjoined);
	mBjoined = true;
	pthread_join(mThreadId,NULL);
}
void* Thread::RunInThread(void *obj)
{
	Thread *thread = static_cast<Thread *>(obj);
	thread->mThreadFunc();
	return NULL;
}
}
#endif  // _TEMO_THREAD_H_
