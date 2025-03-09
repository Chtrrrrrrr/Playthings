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
HWND WindowHWND = NULL; //���ھ��
int DrawZeroPoint; //ͼ��������
LPCWSTR GameWindowTitle = L"|>>                                                                                                                               |��ʵ-Falsrue|                                                                                                            <<|";
//������Ŀ��ַ������ӵ���Ӳ���룬++
string DialogString[100] = {
    "�٣�����һ������Ҫ���㡭�������е㼬�֣����������ֻ�����ܽ��\n����\n��ʵ��Ҳ��̫�����������ô���£���������һ��ȥ������\n��������\nŶ���������ˣ�\n����������������\n����ʲô��û���ˡ���",
    "�þò������������ڻ����ˣ����ǵ�����û�����\n���������������C���������",
    "�㡭��ȷ��Ҫ����������������������Ŭ����׷ѵģ�\n*�������ȡ��,��c���������*",
    "�ã�������\n",
};


//--���ܺ���

// ��͸����ͼ����
// ������
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
void TransparentIMAGE(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
// ��͸����ͼ����������͸��ֵ
// ������
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		tou�� ������͸��ֵ
void TransparentIMAGE(IMAGE* dstimg, int x, int y, IMAGE* srcimg, BYTE tou)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, tou, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
//��ȡָ����
string ReadLine(char* filename, int line)
{
    int i = 0;
    string temp;
    fstream file;
    file.open(filename, ios::in);

    if (line <= 0)
    {
        return "Error 1: �������󣬲���Ϊ0������";
    }

    if (file.fail())
    {
        return "Error 2: �ļ������ڡ�";
    }

    while (getline(file, temp) && i < line - 1)
    {
        i++;
    }

    file.close();
    return temp;
}
//���д���
auto CenterWindowF(_In_ const HWND& winHandle) -> void
{
    RECT rect{ };
    GetWindowRect(winHandle, &rect);
    const auto width{ rect.right - rect.left };
    const auto height{ rect.bottom - rect.top };
    const auto cx{ GetSystemMetrics(SM_CXFULLSCREEN) }; // ȡ��ʾ����Ļ�߿�
    const auto cy{ GetSystemMetrics(SM_CYFULLSCREEN) };
    const auto x{ cx / 2 - width / 2 };
    const auto y{ cy / 2 - height / 2 };
    MoveWindow(winHandle, x, y, width, height, false); // �ƶ�����λ�þ���
}
//�Ŵ��ı�

//--��Ϸ����

//�Ի���Order���Ի���� X��Y����ʾλ�ã��Ի����ݵ��м䣩 FontSize�������С���� Color��������ɫ�������һ�ΰ��µ�����
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

IMAGE WindowCanvas(300, 175); //��ʾ���ݵ�ͼ����Ⱦʱͳһ�Ŵ�4���������زľͿ�����С�ı����� �ȷ����н�ʡ�ռ�
IMAGE TrueWindowCanvas(1200, 700), ClearIMAGE;
//����ھӷŴ���
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼ��С
void NearestNeighborImage(IMAGE* dstimg, IMAGE* srcimg, int width, int height)
{
	// ��ʼ����ͼ
	dstimg->Resize(width, height);
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);

	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();

	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// ����
	float h_scale_rate = (float)src_height / height;
	float w_scale_rate = (float)src_width / width;

	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			// ��������ԭͼ��Ӧ������
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