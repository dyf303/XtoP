#include <iostream>

#include "LoadXML.h"

using namespace std;

int main(int argv, char * argc[])
{
	if (argv < 2)
	{
		return 0;
	}
	else
	{
		CreateSaveDoc();
		LoadFromXML(argc[1]);
		SaveToplist();
	}

	std::cout << "Complate convert " << argc[1] << "to plist file." << std::endl;
	//getchar();
	return 0;
}