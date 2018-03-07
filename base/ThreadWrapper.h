#ifndef _THREAD_WRAPPER_H_
#define _THREAD_WRAPPER_H_

#include <thread>
namespace TEMO
{

class ThreadWrapper
{
public:
	enum class DtorAction {join,detach};
	
	ThreadWrapper(std::thread&& thread,DtorAction action):m_action(action),m_thread(std::move(thread)){}
	
	~ThreadWrapper()
	{
		if (m_thread.joinable())
		{
			if (m_action == DtorAction::join){
				m_thread.join();
			}else{
				m_thread.detach();
			}
		}
	}
	
	
	std::thread & Get() { return m_thread;}
		
	ThreadWrapper(ThreadWrapper && wrapper) = default;
	ThreadWrapper& operator=(ThreadWrapper & wrapper) = default;
private:
	std::thread m_thread;
	DtorAction 	m_action;
};
}



#endif
