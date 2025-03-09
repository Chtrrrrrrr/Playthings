/*****************************************************************//**
 * \file   main.cpp
 * \brief  
 * 
 * 
 * \author Chtrrrrrrr
 * \date   February 2024
 * \see https://codebus.cn/huidong/rotateimage-alpha
 *		  https://blog.csdn.net/santook/article/details/10949765
 *********************************************************************/
#include <easyx.h>
#include <math.h>
#include <Windows.h>
#include <iostream>
using namespace std;

#pragma comment( lib, "MSIMG32.LIB")

#define PI 3.1415926

// 旋转图像（保留透明信息，自适应大小）
// pImg 原图像
// radian 旋转弧度
// bkcolor 背景填充颜色
// 返回旋转后的图像
IMAGE RotateImage_Alpha(IMAGE* pImg, double radian, COLORREF bkcolor = BLACK)
{
	radian = -radian;														// 由于 y 轴翻转，旋转角度需要变负
	float fSin = (float)sin(radian), fCos = (float)cos(radian);				// 存储三角函数值
	float fNSin = (float)sin(-radian), fNCos = (float)cos(-radian);
	int left = 0, top = 0, right = 0, bottom = 0;							// 旋转后图像顶点
	int w = pImg->getwidth(), h = pImg->getheight();
	DWORD* pBuf = GetImageBuffer(pImg);
	POINT points[4] = { {0, 0}, {w, 0}, {0, h}, {w, h} };					// 存储图像顶点
	for (int j = 0; j < 4; j++)												// 旋转图像顶点，搜索旋转后的图像边界
	{
		points[j] = {
			(int)(points[j].x * fCos - points[j].y * fSin),
			(int)(points[j].x * fSin + points[j].y * fCos)
		};
		if (points[j].x < points[left].x)	left = j;
		if (points[j].y > points[top].y)	top = j;
		if (points[j].x > points[right].x)	right = j;
		if (points[j].y < points[bottom].y)	bottom = j;
	}

	int nw = points[right].x - points[left].x;
	int nh = points[top].y - points[bottom].y;
	int nSize = nw * nh;
	int offset_x = points[left].x < 0 ? points[left].x : 0;					// 旋转后图像超出第一象限的位移（据此调整图像位置）
	int offset_y = points[bottom].y < 0 ? points[bottom].y : 0;

	IMAGE img(nw, nh);
	DWORD* pNewBuf = GetImageBuffer(&img);
	if (bkcolor != BLACK)													// 设置图像背景色
		for (int i = 0; i < nSize; i++)
			pNewBuf[i] = BGR(bkcolor);

	for (int i = offset_x, ni = 0; ni < nw; i++, ni++)						// i 用于映射原图像坐标，ni 用于定位旋转后图像坐标
	{
		for (int j = offset_y, nj = 0; nj < nh; j++, nj++)
		{
			int nx = (int)(i * fNCos - j * fNSin);							// 从旋转后的图像坐标向原图像坐标映射
			int ny = (int)(i * fNSin + j * fNCos);
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)						// 若目标映射在原图像范围内，则拷贝色值
				pNewBuf[nj * nw + ni] = pBuf[ny * w + nx];
		}
	}

	return img;
}

// 透明贴图（by 慢羊羊）
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

/*
keybd_event(0xAF, 0, 0, 0);
keybd_event(0xAF, 0, KEYEVENTF_KEYUP, 0)

keybd_event(0xAE, 0, 0, 0);
keybd_event(0xAE, 0, KEYEVENTF_KEYUP, 0)

keybd_event(0xAD, 0, 0, 0);
keybd_event(0xAD, 0, KEYEVENTF_KEYUP, 0)
*/

int main()
{
	initgraph(245,300);
	setfillcolor(LIGHTGRAY);
	IMAGE i1, i2, i3;
	float x=0;
	ExMessage mmsg;
	loadimage(&i1, _T("1_1.png"));
	loadimage(&i2, _T("2.png"));
	loadimage(&i3, _T("1_2.png"));
	IMAGE Tmep = i2;
	int volume = 0;
	for (;;)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &i1);
		transparentimage(NULL, 150-Tmep.getwidth()/2, 155-Tmep.getheight()/2, &Tmep);
		transparentimage(NULL, 0, 0, &i3);
		solidcircle(27+x, 264, 21);
		FlushBatchDraw();
		peekmessage(&mmsg, EX_MOUSE);
		//187
		//2.15 volume/pex
		//3*PI/4
		if (mmsg.x >= 26 && mmsg.y >= 241 && mmsg.x <= 213 && mmsg.y <= 286)
		{
			if (mmsg.lbutton == true&&mmsg.x!=x+27)
			{
				x = mmsg.x - 27;
				//cout << x;
				Tmep = RotateImage_Alpha(&i2, 2.0*PI-(3.0 * PI / 4.0) * (x / 187.0));

				if (int(x)*100/187 % 2 != 0)x += 1;
				if (x * 100 / 187 > volume)
				{
					for (int i = 0; i < ((x * 100 / 187) - volume) / 2&&volume<=100; i++)
					{
						keybd_event(0xAF, 0, 0, 0);
						keybd_event(0xAF, 0, KEYEVENTF_KEYUP, 0);
						volume += 2;
					}
				}
				else if (x * 100 / 187 < volume)
				{
					for (int i = 0; i < (volume - (x * 100 / 187)) / 2&&volume>=0; i++)
					{
						keybd_event(0xAE, 0, 0, 0);
						keybd_event(0xAE, 0, KEYEVENTF_KEYUP, 0);
						volume -= 2;
					}
				}
			}
		}
		//cout << mmsg.x << " " << mmsg.y << endl;
		Sleep(1);
	}
	closegraph();
	return 0;
}


