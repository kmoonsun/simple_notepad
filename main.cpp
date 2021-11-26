#include "ConsoleInterface.h"


int main()
{
	DataManager manager;

	ConsoleInterface console(manager);
	console.EntryMenu();
	
	return 0;
}
