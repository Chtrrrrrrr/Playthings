#include<easyx.h>
#include<Windows.h>
#include<tchar.h>
#include"resource.h"
#define random(a,b) (rand()%(b-a)+a)

int main()
{
	initgraph(1200, 600);
	setbkcolor(WHITE);
	clearcliprgn();
	IMAGE javaico, background;
	loadimage(&javaico, _T("PNG"),MAKEINTRESOURCE(IDB_PNG1));
	loadimage(&background, _T("PNG"),MAKEINTRESOURCE(IDB_PNG2));
	setfillcolor(RED);
	BeginBatchDraw();
	solidrectangle(0, 0, 1600, 300);
	putimage(70,10 ,&javaico);
	settextstyle( 55,30, _T("微软雅黑"));
	settextcolor(RED);
	outtextxy(250, 400, _T("欢迎使用《JAVA》2安装程序"));
	settextstyle(35, 10, _T("微软雅黑"));
	outtextxy(250, 460, _T("《JAVA》2  更《快》更《便杰》！"));
	outtextxy(0, 570, _T("本程序不会在你的电脑中安装任何程序（这是认真的）"));
	settextstyle(55, 30, _T("微软雅黑"));
	solidrectangle(800, 500, 1600, 570);
	outtextxy(950, 510, _T("安装"));
	EndBatchDraw();
	for (ExMessage mmsg;;)
	{
		peekmessage(&mmsg, EM_MOUSE);
		if (mmsg.lbutton == true && mmsg.x >= 800 && mmsg.x < 1600 && mmsg.y>500 && mmsg.y < 570)
		{
			break;
		}
	}
	clearcliprgn();
	for (int i = 0; i < 1200; i += 10)
	{
		solidrectangle(20, 400, 20 + i, 470);
		outtextxy(30 + i, 410, _T("焯焯！"));
		outtextxy(random(0, 1200), random(0, 600), _T("焯焯"));
		Sleep(7);
	}
	clearcliprgn();
	settextstyle(145, 100, _T("微软雅黑"));
	outtextxy(70, 30, _T("《JAVA》2"));
	settextstyle(55, 30, _T("微软雅黑"));
	outtextxy(70, 230, _T("           《JAVA》2 安装成功"));
	outtextxy(70, 290, _T("现在《JAVA》2可以在你的电脑里焯焯了"));
	outtextxy(0, 350, _T("也可以运行依靠《JAVA》的MeniCreft了"));
	settextstyle(35, 10, _T("微软雅黑"));
	outtextxy(40, 420, _T("《JAVA》2依靠老旧的技术进行了负优化，可以使大刑程序的帧率增加-60"));
	solidrectangle(800, 500, 1600, 570);
	settextstyle(55, 30, _T("微软雅黑"));
	outtextxy(950, 510, _T("完成"));
	for (ExMessage mmsg;;)
	{
		peekmessage(&mmsg, EM_MOUSE);
		if (mmsg.lbutton == true && mmsg.x >= 800 && mmsg.x < 1600 && mmsg.y>500 && mmsg.y < 570)
		{
			break;
		}
	}
	closegraph();
	return 0;
}