#include "chat.cpp"

int main()
{
	HashTable users;
	users.reg((char*)"vasya", 2345);
	users.reg((char*)"kolya", 1234);
	users.reg((char*)"petya", 3456);

	users.printInfo();

	return 0;
}