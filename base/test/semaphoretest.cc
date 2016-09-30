#include "../Semaphore.h"
#include <stdio.h>
int main()
{
	TEMO::Semaphore s(1);
	printf("11\n");
	s.Wait();
	printf("22\n");
	s.Wait();
	return 0;
}