#ifndef _THREAD_NAME_H_
#define _THREAD_NAME_H_

#include <thread>
#include <string>

namespace TEMO
{
	
void SetThreadName(std::thread::id tid,std::string name);

void SetCurrentThreadName(std::string name);
//void SetThreadName(pthread_t pid,std::string name);

std::string GetThreadName(std::thread::id tid);
	
std::string GetCurrentThreadName();
	
}


#endif 