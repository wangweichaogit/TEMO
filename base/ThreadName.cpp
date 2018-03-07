#include "ThreadName.h"

namespace TEMO
{
static constexpr size_t kMaxThreadNameLength= 15;
void SetThreadName(std::thread::id tid,std::string name)
{
	
}

void SetCurrentThreadName(std::string name);
//void SetThreadName(pthread_t pid,std::string name);

std::string GetThreadName(std::thread::id tid)
{
	
}
	
std::string GetCurrentThreadName();
}