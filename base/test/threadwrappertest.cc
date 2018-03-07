#include "../ThreadWrapper.h"

#include <iostream>
using TEMO::ThreadWrapper;

int main()
{
	ThreadWrapper t(std::thread( [](){
		std::cout<<"dsd"<<std::endl;
		
	}),ThreadWrapper::DtorAction::join);

	getchar();	
	return 0;
}
