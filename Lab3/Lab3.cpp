
#include <iostream>
#include "Dll.h"


const char hello[] = "Hello, world\n";
const char love[] = "I love you\n";


int main()
{
	size_t size = strlen(love) + 1;
	char* dest = (char*)malloc(size * sizeof(char));
	
    strcpy_s(dest, size, love);

	
	std::cout << dest << std::endl;
	
	ReplaceMemory(love, hello);

	std::cout << dest << std::endl;
	
}


