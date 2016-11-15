#include "usage.h"
#include <iostream>

int main()
{
NetCheck impl;
if (impl.netIsOk("136.17.79.116","114.114.114.114")) {
	std::cout<<"net is okay"<<std::endl;
}
else {
	std::cout<<"net is error"<<std::endl;
}
return 0;
}
