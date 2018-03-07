#ifndef _SIGLETION_H_
#define _SIGLETION_H_

#include <memory>
#include <mutex>

class SigletonBase: private std::noncopyable
{
public:
	virtual ~SigletonBase() = default;
private:
};





#endif
