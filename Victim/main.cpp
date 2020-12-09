
#include <iostream>
#include <Windows.h>

const char hello[] = "Hello, world\n";


int main()
{
	char* s = new char[strlen(hello) + 1];
	strcpy_s(s, strlen(hello) + 1, hello);
	std::cout << s << std::endl;
	std::cout << GetCurrentProcessId() << std::endl;
	std::cin.get();
	std::cout << s << std::endl;
}