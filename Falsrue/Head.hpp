#pragma once
#include <easyx.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>
#include <string.h>
#include <random>
#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#include <mmsystem.h>
#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "Winmm.lib")
using namespace std;
#define RandomNumbers(a,b) (rand()%(b-a+1)+a)

const double PI = 3.14159265358979;
HWND WindowHWND = NULL; //窗口句柄
int DrawZeroPoint; //图像绘制零点
LPCWSTR GameWindowTitle = L"|>>                                                                                                                               |虚实-Falsrue|                                                                                                            <<|";
//草泥马的宽字符，老子当场硬编码，++
string DialogString[100] = {
    "嘿，我有一个任务要给你……呃，有点棘手，不过这件事只有你能解决\n……\n其实我也不太清楚到底是怎么回事，反正咱们一起去看看吧\n…………\n哦，不！坏了！\n……………………\n……什么都没有了……",
    "好久不见啊，你终于回来了，咱们的任务还没完成呢\n按任意键继续，按C键清除记忆",
    "你……确定要重新来吗？那样我们曾经的努力会白费的！\n*按任意键取消,按c键清除记忆*",
    "好！继续！\n",
};


//--功能函数

// 半透明贴图函数
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
void TransparentIMAGE(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
// 半透明贴图函数，附带透明值
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		tou： 附带的透明值
void TransparentIMAGE(IMAGE* dstimg, int x, int y, IMAGE* srcimg, BYTE tou)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, tou, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
//获取指定行
string ReadLine(char* filename, int line)
{
    int i = 0;
    string temp;
    fstream file;
    file.open(filename, ios::in);

    if (line <= 0)
    {
        return "Error 1: 行数错误，不能为0或负数。";
    }

    if (file.fail())
    {
        return "Error 2: 文件不存在。";
    }

    while (getline(file, temp) && i < line - 1)
    {
        i++;
    }

    file.close();
    return temp;
}
//居中窗口
auto CenterWindowF(_In_ const HWND& winHandle) -> void
{
    RECT rect{ };
    GetWindowRect(winHandle, &rect);
    const auto width{ rect.right - rect.left };
    const auto height{ rect.bottom - rect.top };
    const auto cx{ GetSystemMetrics(SM_CXFULLSCREEN) }; // 取显示器屏幕高宽
    const auto cy{ GetSystemMetrics(SM_CYFULLSCREEN) };
    const auto x{ cx / 2 - width / 2 };
    const auto y{ cy / 2 - height / 2 };
    MoveWindow(winHandle, x, y, width, height, false); // 移动窗口位置居中
}
//放大四倍

//--游戏内容

//对话，Order：对话序号 X、Y：显示位置（对话内容的中间） FontSize：字体大小（宽） Color：字体颜色返回最后一次按下的内容
char DialogOutput(int Order,int X,int Y,int FontSize,int Color)
{
    settextstyle(FontSize, 0, "Unifont");
    setbkmode(TRANSPARENT);
    settextcolor(Color);
    string dialog = DialogString[Order];
    string temp;
    for (int nowchar = 0; dialog[nowchar] != '\0'; nowchar++)
    {
        if (dialog[nowchar] == '\n')
        {
            _getch();
            temp.clear();
            nowchar++;
            cleardevice();
        }
        temp += dialog[nowchar];
        cleardevice();
        outtextxy(X - (textwidth(temp.c_str())/2), Y, temp.c_str());
        Sleep(1);
    }
    return _getch();
}

IMAGE WindowCanvas(300, 175); //显示内容的图像，渲染时统一放大4倍，这样素材就可以缩小四倍画， 既方便有节省空间
IMAGE TrueWindowCanvas(1200, 700), ClearIMAGE;
//最近邻居放大函数
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图大小
void NearestNeighborImage(IMAGE* dstimg, IMAGE* srcimg, int width, int height)
{
	// 初始化新图
	dstimg->Resize(width, height);
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);

	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();

	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// 比例
	float h_scale_rate = (float)src_height / height;
	float w_scale_rate = (float)src_width / width;

	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			// 比例计算原图相应坐标中
			int i_scale = h_scale_rate * iy;
			int j_scale = w_scale_rate * ix;

			DWORD* p = GetImageBuffer(srcimg);
			int psc_width = srcimg->getwidth();
			int psc_height = srcimg->getheight();

			for (int iy = 0; iy < i_scale; iy++)
			{
				p += psc_width;
			}

			dst[ix] = p[j_scale];
		}
		dst += dst_width;
		src += src_width;
	}
}
void WindowCanvasOutput()
{
    NearestNeighborImage(&TrueWindowCanvas, &WindowCanvas, 1200, 700);
    TransparentIMAGE(NULL, 0, 0, &TrueWindowCanvas);
}
void WindowCanvasClear()
{
    TransparentIMAGE(&WindowCanvas, 0, 0, &ClearIMAGE);
}