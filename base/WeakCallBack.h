/*
Èõ»Øµ÷Àà

*/

#ifndef _WEAKCALLBACK_H_
#define _WEAKCALLBACK_H_
#include <functional>
#include <memory>
#include <iostream>

	
template<typename CLASS>
class WeakCallBack
{
	public:
		WeakCallBack(const std::weak_ptr<CLASS> &obj,const std::function<void (CLASS *)> &func):_function(func),_object(obj) {}

		
		void operator()() const
		{
			std::shared_ptr<CLASS> ptr = _object.lock();
			if(ptr)
				{ 
					_function(ptr.get());
				}
		}
	
	private:
		std::weak_ptr<CLASS> _object;
		std::function<void (CLASS *)> _function;
};


template<typename CLASS>
WeakCallBack<CLASS> makeWeakCallBack(const std::shared_ptr<CLASS> &obj,void (CLASS::*func)() )
{
	return WeakCallBack<CLASS>(obj,func);
}
#endif