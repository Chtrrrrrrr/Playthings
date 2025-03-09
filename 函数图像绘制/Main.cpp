#include <easyx.h>
#include <cmath>
#include <iostream>
#include <conio.h>
using namespace std;
const int Width = 1920, Height = 1080;
const int X0 = Width/2, Y0 = Height/2;

inline int GetRelativeX(int x)
{
	return X0 + x;
}
inline int GetRelativeY(int y)
{
	return Y0 - y;
}

int Zoom = 100;
void Net()
{
	//X+
	setlinecolor(RGB(237,237,237));
	for (float i = 0; i * Zoom <= Width / 2; i += 0.2)
	{
		line(GetRelativeX(i * Zoom), 0, GetRelativeX(i * Zoom), Height);
	}
	for (float i = 0; i * Zoom >= -Width / 2; i -= 0.2)
	{
		line(GetRelativeX(i * Zoom), 0, GetRelativeX(i * Zoom), Height);
	}
	setlinecolor(RGB(178,178,178));
	for (float i = 0; i * Zoom <= Width / 2; i ++)
	{
		line(GetRelativeX(i * Zoom), 0, GetRelativeX(i * Zoom), Height);
	}
	for (float i = 0; i * Zoom >= -Width / 2; i--)
	{
		line(GetRelativeX(i * Zoom), 0, GetRelativeX(i * Zoom), Height);
	}
	//Y+
	setlinecolor(RGB(237, 237, 237));
	for (float i = 0; i * Zoom <= Width / 2; i += 0.2)
	{
		line(0, GetRelativeY(i * Zoom), Width, GetRelativeY(i * Zoom));
	}
	for (float i = 0; i * Zoom >= -Width / 2; i -= 0.2)
	{
		line(0, GetRelativeY(i * Zoom), Width, GetRelativeY(i * Zoom));
	}
	setlinecolor(RGB(178, 178, 178));
	for (float i = 0; i * Zoom <= Width / 2; i++)
	{
		line(0, GetRelativeY(i * Zoom), Width, GetRelativeY(i * Zoom));
	}
	for (float i = 0; i * Zoom >= -Width / 2; i--)
	{
		line(0, GetRelativeY(i * Zoom), Width, GetRelativeY(i * Zoom));
	}

	setlinecolor(BLACK);
	line(0, Height / 2, Width, Height / 2);
	line(Width / 2, 0, Width / 2, Height);
	setlinecolor(RGB(115, 115, 115));
	line(0, Height / 2-1, Width, Height / 2-1);
	line(0, Height / 2+1, Width, Height / 2+1);
	line(Width / 2-1, 0, Width / 2-1, Height);
	line(Width / 2+1, 0, Width / 2+1, Height);

	settextstyle(12, 0, L"Symbol");
	setbkmode(TRANSPARENT);
	for (float i = 0; i * Zoom <= Width / 2; i++)
	{
		outtextxy(GetRelativeX(i * Zoom)-getwidth()/2, Height / 2, );
	}
	for (float i = 0; i * Zoom >= -Width / 2; i--)
	{
		line(GetRelativeX(i * Zoom), 0, GetRelativeX(i * Zoom), Height);
	}
	for (float i = 0; i * Zoom <= Width / 2; i++)
	{
		line(0, GetRelativeY(i * Zoom), Width, GetRelativeY(i * Zoom));
	}
	for (float i = 0; i * Zoom >= -Width / 2; i--)
	{
		line(0, GetRelativeY(i * Zoom), Width, GetRelativeY(i * Zoom));
	}
}
int main()
{
	initgraph(Width, Height);
	setbkcolor(WHITE);
	clearcliprgn();
	BeginBatchDraw();
	Net();
	FlushBatchDraw();
	_getch();
	closegraph();
	return 0;
}