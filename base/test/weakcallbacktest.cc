#include "WeakCallBack.h"
#include <iostream>

using namespace std;

class test
{
	public:
		void testa()
		{
			cout<<"testa"<<endl;
		}
};

int main()
{
	shared_ptr<test> pt(new test()); 
	WeakCallBack<test> pw = makeWeakCallBack(pt,&test::testa);
	pw();
	cout<<"-----"<<endl;
	pt.reset();
	pw();
	cout<<"-----"<<endl;
	return 0;
}