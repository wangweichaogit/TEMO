#include "../Atomic.h"
#include <stdio.h>

int main()
{
	TEMO::AtomicInt32 a1;
	a1.getAndSet(64);
	
	printf("%d\n",a1.get());
	a1.increment();
	printf("%d\n",a1.get());
	a1.decrement();
	printf("%d\n",a1.get());
	
	a1.addAndGet(32);
	printf("%d\n",a1.get());
	
	a1.addAndGet(32);
	printf("%d\n",a1.get());
	
	return 0;
}