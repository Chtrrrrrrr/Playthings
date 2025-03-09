#include<Windows.h>
#include"resource.h"

int main()
{
	system("title Rammap自动清理程序");
	system("RAMMap-64bit -Ew");
	system("RAMMap-64bit -Es");
	//system("RAMMap-64bit -Em");
	//system("RAMMap-64bit -Et");
	//system("RAMMap-64bit -E0");
	return 0;
}