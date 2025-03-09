#pragma once
#include<easyx.h>
#include<Windows.h>
#include<conio.h>
#include<iostream>
#include<cmath>
#include <mmsystem.h>
#include<dsound.h>
#pragma comment(lib, "WINMM.LIB")
using namespace std;
#define random(a,b) (rand()%(b-a+1)+a)
#define animation 200
void drawAi(int  picture_x, int picture_y, IMAGE* picture) //输出一个有透明度的图片picture_x:开始x,picture_y:开始y,* picture:图片指针
														   //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD *dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD *draw = GetImageBuffer();
	DWORD *src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

					 // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void start()
{
	settextcolor(WHITE);
	settextstyle(270, 400, _T("System"));
	for (int i = 0; i <= 255; i++)
	{
		settextcolor(RGB(i, i, i));
		outtextxy((750 - textwidth(_T("Undertale"))) / 2, 150, _T("Undertale"));
		Sleep(5);
	}
	Sleep(200);
	string start_text = "Undertale-Fight with Fuckerpig   大战野猪";
	string start_text_now = " ";
	settextstyle(35, 15, _T("System"));
	for (int i = 0; i <= start_text.length(); i++)
	{
		start_text_now += start_text[i];
		outtextxy((750 - textwidth(start_text_now.c_str())) / 2, 300, start_text_now.c_str());
		Sleep(40);
	}
	_getch();
}

IMAGE background, fuckerpig_body, choose_heart, heart, hurt_image, tell_bar;
char ctrl = NULL;
int fuckerpig_ani = animation, textbarwidth = 650, textnow = 0, tellnow = 0;
int eye_x = 5, eye_y = 3, heart_x = 65, heart_y = 65; //野猪眼睛的位置 <=10 心的位置
bool fuckerpig_now = false, angry = false;
int type = 0, style = 0;//type类型，0：攻击、1：行动、2：物品。style进度，0：提示、1：预览、2：选择对象、3：选择操作（如果时进攻则是攻击窗口）、4：对手说话、5：战斗窗口
int choose = 1; //选择的第几个1-4
int blood = 30, tell_plus=0;
int hurt = 0; //攻击从左到右的距离
string text[7] = //提示内容
{ 
	"* 野 猪 挡 住 了 去 路 ！",
	"* 野 猪 不 屑 的 哼 唧 哼 唧 。",
	"* 野 猪 发 觉 自 己 有 点 疲 倦 。",
	"* 野 猪 噜 噜 的 喘 气 。",
	"* 野 猪 累 得 要 命 。",
	"* 野 猪 累 死 了 . . .",
	"你 赢 了,获 得 了 28LV 和 64金钱！"
};
string tell[7] =  //说的话
{
	"你太逊了！",
	"花儿在枯萎鸟儿在幽泣。",
	"你的攻击对我毫无作用。",
	"你打的过我吗？自欺欺人的家伙。",
	"拜托，你很弱诶。",
	"*呼噜噜，呼噜噜",
	"M I S S"
};
// 6*6 45 34
void prt()
{
	drawAi(0, 0, &background);
	drawAi(300, 100 + (fuckerpig_now == true ? 5 : 0), &fuckerpig_body);
	setfillcolor(angry ? RED: WHITE);
	setlinecolor(angry ? RED : WHITE);
	fillrectangle(345 + eye_x, 134 + (fuckerpig_now == true ? 5 : 0) + eye_y, 351 + eye_x, 140 + (fuckerpig_now == true ? 5 : 0) + eye_y);
	setlinecolor(WHITE);
	setlinecolor(WHITE);
	rectangle((750 - textbarwidth) / 2, 320, (750 - textbarwidth) / 2 + textbarwidth, 490);
	outtextxy(50, 500, _T("野 猪       LV 114     HP            /30"));
	setfillcolor(YELLOW);
	fillrectangle(500, 503, 500 + blood*2, 528);
	outtextxy(570, 500, blood / 10 + '0');
	outtextxy(590, 500, blood % 10 + '0');
	setfillcolor(WHITE);
	setbkmode(TRANSPARENT);
	switch (style)
	{
	case 0:
	{
		outtextxy(55, 325, text[textnow].c_str());
		drawAi(57+type*189, 550, &choose_heart);
		if (textbarwidth != 650)
			textbarwidth = 650;
		break;
	}
	case 1:
	{
		if (type == 2)
		{
			outtextxy(91, 325, _T("* 你 的 背 包"));
		}
		else
		{
			outtextxy(91, 325, _T("* 野 猪"));
		}
		drawAi(57 + type * 189, 550, &choose_heart);
		break;
	}
	case 2:
	{
		if (type == 2)
		{
			outtextxy(91, 325, _T("* 你 的 背 包"));
		}
		else
		{
			outtextxy(91, 325, _T("* 野 猪"));
		}
		drawAi(55, 325, &choose_heart);
		break;
	}
	case 3:
	{
		switch (type)
		{
		case 0:
		{
			if (hurt < textbarwidth-10)
				hurt+=2;
			else
				hurt = textbarwidth-10;
			drawAi(50, 325, &hurt_image);
			fillrectangle(50 + hurt, 320, 50 + hurt + 5, 490);
			break;
		}
		case 1:
		{
			outtextxy(100, 325, _T("* 交 谈                      * 询 问"));
			outtextxy(100, 425, _T("* 准 备 进 攻             * 偷 袭"));
			drawAi(55 + (choose % 2 ? 0 : 380), 325 + (choose <= 2 ? 0 : 100), &choose_heart);
			break;
		}
		case 2:
		{
			outtextxy(100, 325, _T("* 饼 干                      * 好 鸡 汤"));
			outtextxy(100, 425, _T("* 蜘 蛛 果 汁             * 金 苹 果"));
			drawAi(55 + (choose % 2 ? 0 : 380), 325 + (choose <= 2 ? 0 : 100), &choose_heart);
			break;
		}
		}
		break;
	}
	case 4:
	{
		drawAi(450, 50, &tell_bar);
		settextstyle(30, 10, _T("System"));
		settextcolor(angry == false ? BLACK : RED );
		tell_plus = angry == true ? random(0, 5) : 0;
		if (tell[tellnow].length() <= 14)
			outtextxy(455 + tell_plus, 55 + tell_plus, (tell[tellnow].c_str()));
		else
		{
			outtextxy(455 + tell_plus, 55 + tell_plus, (tell[tellnow].substr(0,14).c_str()));
			outtextxy(455 + tell_plus, 85 + tell_plus, (tell[tellnow].substr(14, tell[tellnow].size()-14).c_str()));
		}
		settextstyle(40, 20, _T("System"));
		settextcolor(WHITE);
		if (textbarwidth > 170)
		{
			textbarwidth-=3;
		}
		drawAi((750 - textbarwidth) / 2 + heart_x, 320 + heart_y, &heart);
		break;
	}
	case 5:
	{
		drawAi((750 - textbarwidth) / 2 + heart_x, 320 + heart_y, &heart);
	}
	}
}
void game()
{
	cleardevice();
	settextstyle(40, 20, _T("System"));
	loadimage(&background, _T(".\\game-release\\background.png"));
	loadimage(&fuckerpig_body, _T(".\\game-release\\fuckerpig_body.png"));
	loadimage(&choose_heart, _T(".\\game-release\\choose_heart.png"));
	loadimage(&heart, _T(".\\game-release\\heart.png"));
	loadimage(&hurt_image, _T(".\\game-release\\hurt.png"));
	loadimage(&tell_bar, _T(".\\game-release\\talk.png"));
	drawAi(0, 0, &background);
	settextcolor(WHITE);
	for (;;)
	{
		BeginBatchDraw();
		prt();
		FlushBatchDraw();
		if (_kbhit()) ctrl = _getch();
		if (fuckerpig_ani == 0 && !angry)
		{
			eye_x = random(0, 10);
			eye_y = random(0, 10);
		}
		else if(angry)
		{
			eye_x = random(0, 10);
			eye_y = random(0, 10);
		}
		if(fuckerpig_ani>0)
			fuckerpig_ani--;
		else
		{
			fuckerpig_ani=animation;
			fuckerpig_now = !fuckerpig_now;
			loadimage(&fuckerpig_body, _T(".\\game-release\\fuckerpig_body.png"),150, 100 - (fuckerpig_now == true ? 5 : 0));
		}
		if (ctrl == 13)
		{
			if (style < 5)
				style++;
			else
			{
				style = 0;
				textnow++;
			}
			if (style == 3)
			{
				tellnow = random(0, 5);
			}
			if (style == 3)
			{
				if (type == 1 && choose == 4)
				{
					angry = true;
				}
				else if (type == 2)
				{
					blood = 30;

				}
			}
			if (style == 5)
			{
				textbarwidth = 170;
			}
			if (textnow == 5 && style == 1)
			{
				textnow++;
				style--;
			}
			if (textnow == 6 && style == 1)
			{
				break;
			}
			if (type == 0 && style == 3)
			{
				tellnow = 6;
			}
		}
		if (ctrl == 75) //left
		{
			if (style == 1)
			{
				if (type == 0)
					type = 2;
				else
					type--;
			}
			if (style == 3 && type == 1 || type == 2)
			{
				if (choose == 1)
					choose = 4;
				else
					choose--;
			}
			if (style >= 4 && heart_x > 0)
			{
				heart_x-=7;
			}
		}
		else if (ctrl == 77) //right 
		{
			if (style == 1)
			{
				if (type == 2)
					type = 0;
				else
					type++;
			}
			if (style == 3 && type == 1 || type == 2)
			{
				if (choose == 4)
					choose = 1;
				else
					choose++;
			}
			if (style >= 4 && heart_x < 130)
			{
				heart_x += 7;
			}
		}
		else if (ctrl == 72) //up
		{
			if (style == 3 && type == 1 || type == 2)
			{
				if (choose == 1 || choose == 2)
					choose += 2;
				else
					choose -= 2;
			}
			if (style >= 4 && heart_y > 0)
			{
				heart_y -= 7;
			}
		}
		else if (ctrl == 80) //down
		{
			if (style == 3 && type == 1 || type == 2)
			{
				if (choose == 3 || choose == 4)
					choose -= 2;
				else
					choose += 2;
			}
			if (style >= 4 && heart_y < 130)
			{
				heart_y += 7;
			}
		}
		ctrl = NULL;
	}

}