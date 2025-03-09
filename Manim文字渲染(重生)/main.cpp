#include <iostream>
#include <easyx.h>
#include "windows.system.h"
#include <conio.h>
#include <cmath>
#include <string>
#include <string.h>
#include <cstring>

//#pragma comment(lib,"winmm.lib") // 链接多媒体库
using namespace std;

//参数
const int WindowWidth = 1920; // 宽
const int WindowHeight = 1080; // 高
const float FramePerSecond = 30; // 帧率
const float AloneTexRenderTime = 1.25; // 单个字符的渲染时间，单位秒
const int MAXfoot = 2000; //单次递归最大值
//其他全局变量

//声明
void HpSleep(int);
bool RenderRecursion(IMAGE*, IMAGE*, int, int, int, int, int, COLORREF, int, int);

inline COLORREF GP(int x, int y)
{
	if (x<0 || y<0 || x>WindowWidth || y>WindowHeight) return BLACK;
	else return getpixel(x, y);
}
//既不简单又不强势的函数
inline COLORREF LerpColor(COLORREF color1, COLORREF color2, float t) 
{
	// 提取颜色通道
	BYTE r1 = GetRValue(color1);
	BYTE g1 = GetGValue(color1);
	BYTE b1 = GetBValue(color1);

	BYTE r2 = GetRValue(color2);
	BYTE g2 = GetGValue(color2);
	BYTE b2 = GetBValue(color2);
	// 线性插值每个通道
	BYTE r = static_cast<BYTE>(r1 + (r2 - r1) * t);
	BYTE g = static_cast<BYTE>(g1 + (g2 - g1) * t);
	BYTE b = static_cast<BYTE>(b1 + (b2 - b1) * t);
	return RGB(r, g, b);
}

// 有动画的渲染，CH为字，X、Y坐标，SIZE为大小（平均高度），COLOR颜色（不能为黑色），TEXRENDERBATCH几次一延迟，OUTPUT输出的目标，FONT字体名称
void TexRender2Buffer(LPCTSTR CH, int X, int Y, int SIZE, COLORREF COLOR, float TexRenderBatch = 30, IMAGE* OUTPUT = NULL, LPCTSTR FONT = LPCTSTR(L"Times New Roman Italic"))
{
	//得到字的图片
	settextstyle(SIZE, 0, FONT);
	IMAGE TexImage(textwidth(CH) * 1.2, textheight(CH) * 1.2);
	float EdgePixelNumber = 0;
	SetWorkingImage(&TexImage);
	settextcolor(COLOR);
	settextstyle(SIZE, 0, FONT);
	outtextxy(2, 2, CH);
	//拷贝到数组中方便操作
	IMAGE TexEdge(textwidth(CH) * 1.2, textheight(CH) * 1.2);
	for (int i = 1; i < textwidth(CH) * 1.2 - 1; i++)
		for (int j = 1; j < textheight(CH) * 1.2 - 1; j++)
		{
			//边框判断（只要不是内部的点）
			if (getpixel(i, j) == COLOR && (getpixel(i - 1, j) == BLACK || getpixel(i + 1, j) == BLACK || getpixel(i, j - 1) == BLACK || getpixel(i, j + 1) == BLACK))
			{
				SetWorkingImage(&TexEdge);
				putpixel(i, j, COLOR);
				SetWorkingImage(&TexImage);
				EdgePixelNumber++;
			}
		}
	//绘制边框（前0.5的时间）
	SetWorkingImage(&TexEdge);
	settextstyle(SIZE, 0, FONT);
	for (int i = 0; i < textwidth(CH) * 1.2 - 1; i++)
		for (int j = 0; j < textheight(CH) * 1.2 - 1; j++)
			if (GP(i, j) != BLACK)
				RenderRecursion(&TexEdge, OUTPUT, i, j, X, Y, MAXfoot, COLOR, AloneTexRenderTime * 1000.0 / EdgePixelNumber * TexRenderBatch * 0.5, TexRenderBatch);
	cout << "so?";
	//透明叠加渲染（后0.5的时间）
	float foo = 0.5;
	SetWorkingImage(&TexImage);
	for (float t = 0; t <= 1; t += foo) //线性插值叠加
	{
		for (int i = 0; i < textwidth(CH) * 1.2 - 1; i++) //遍历
			for (int j = 0; j < textheight(CH) * 1.2 - 1; j++)
				if (GP(i, j) != BLACK) //并非全力
				{
					SetWorkingImage(OUTPUT);
					putpixel(X + i, Y + j, LerpColor(GP(X + i, Y + j), COLOR, t));
					SetWorkingImage(&TexImage);
				}
	}
}

//递归渲染 返回值表示是否结束 ORIGINALIMAGE为原图像，OUTPUTIMAGE为目标输出图像，RECURSIONSX、RECURSIONSY为遍历中心位置（相对于原图像），LOCATIONX、LOCATIONY为输出左上角位置（相对于原图像），RESIDUALSTEPS剩余递归步数，COL为颜色，DELAY为延迟时间，TEXRB同上
bool RenderRecursion(IMAGE* ORIGINALIMAGE, IMAGE* OUTPUTIMAGE, int RECURSIONSX, int RECURSIONSY, int LOCATIONX, int LOCATIONY, int RESIDUALSTEPS, COLORREF COL, int DELAY, int TEXRB)
{
	if (!(RESIDUALSTEPS % int(TEXRB))) HpSleep(DELAY);
	//首先绘制
	SetWorkingImage(OUTPUTIMAGE);
	putpixel(LOCATIONX + RECURSIONSX, LOCATIONY + RECURSIONSY, COL);
	//到达最大步数停止
	if (RESIDUALSTEPS <= 0) return true;
	//标记
	SetWorkingImage(ORIGINALIMAGE);
	putpixel(RECURSIONSX, RECURSIONSY, BLACK);
	//判断
	if (GP(RECURSIONSX + 1, RECURSIONSY) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX + 1, RECURSIONSY, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	if (GP(RECURSIONSX - 1, RECURSIONSY) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX - 1, RECURSIONSY, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	if (GP(RECURSIONSX, RECURSIONSY + 1) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX, RECURSIONSY + 1, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	if (GP(RECURSIONSX, RECURSIONSY - 1) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX, RECURSIONSY - 1, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	if (GP(RECURSIONSX + 1, RECURSIONSY + 1) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX + 1, RECURSIONSY + 1, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	if (GP(RECURSIONSX + 1, RECURSIONSY - 1) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX + 1, RECURSIONSY - 1, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	if (GP(RECURSIONSX - 1, RECURSIONSY + 1) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX - 1, RECURSIONSY + 1, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	if (GP(RECURSIONSX - 1, RECURSIONSY - 1) != BLACK) return RenderRecursion(ORIGINALIMAGE, OUTPUTIMAGE, RECURSIONSX - 1, RECURSIONSY - 1, LOCATIONX, LOCATIONY, --RESIDUALSTEPS, COL, DELAY, TEXRB);
	return true;
}

// 精确延时函数
// 使用前：timeBeginPeriod(1);				// 2. 临时提升 Sleep 精度为 1ms
// 	   调用
// 使用后：timeEndPeriod(1);					// 3. 恢复 Sleep 精度
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// 静态变量，记录上一次 tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// 更新 tick

	if (clock() > oldclock)					// 如果已经超时，无需延时
		oldclock = clock();
	else
		while (clock() < oldclock)			// 延时
			Sleep(1);						// 释放 CPU 控制权，降低 CPU 占用率，精度 10~16ms
}

int main()
{
	initgraph(1920, 1080,1);
	IMAGE im;
	loadimage(&im, LPCTSTR(L"D:\\1.png"));
	putimage(0, 0, &im);
	_getch();
	TexRender2Buffer(LPCTSTR(L"{a}"), 100, 100, 300, LIGHTBLUE, 300, NULL, LPCTSTR(L"Times New Roman"));
	//settextstyle(100, 0, _T("Consolas"));
	_getch();
	closegraph();
	return 0;
}
