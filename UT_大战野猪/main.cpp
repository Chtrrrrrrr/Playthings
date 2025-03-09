#include"head.h"

int main()
{
	HWND hwnd=initgraph(750, 600);
	SetWindowTextA(hwnd, "Undertale");
	//start();
	game();

	closegraph();
	return 0;
}