#include <iostream>
#include "HashTable.h"
#include <functional>

int main()
{
	HashTable<int,std::string> table;

	table.add_or_update_mapping(1,"sdsd");
	table.add_or_update_mapping(2,"2222");
	table.add_or_update_mapping(3,"2222");
	
	std::string result = table.value_for(1);
	std::cout<<result.c_str()<<std::endl;
	return 0;
}
