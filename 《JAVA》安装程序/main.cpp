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
	settextstyle( 55,30, _T("΢���ź�"));
	settextcolor(RED);
	outtextxy(250, 400, _T("��ӭʹ�á�JAVA��2��װ����"));
	settextstyle(35, 10, _T("΢���ź�"));
	outtextxy(250, 460, _T("��JAVA��2  �����졷������ܡ���"));
	outtextxy(0, 570, _T("�����򲻻�����ĵ����а�װ�κγ�����������ģ�"));
	settextstyle(55, 30, _T("΢���ź�"));
	solidrectangle(800, 500, 1600, 570);
	outtextxy(950, 510, _T("��װ"));
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
		outtextxy(30 + i, 410, _T("���̣�"));
		outtextxy(random(0, 1200), random(0, 600), _T("����"));
		Sleep(7);
	}
	clearcliprgn();
	settextstyle(145, 100, _T("΢���ź�"));
	outtextxy(70, 30, _T("��JAVA��2"));
	settextstyle(55, 30, _T("΢���ź�"));
	outtextxy(70, 230, _T("           ��JAVA��2 ��װ�ɹ�"));
	outtextxy(70, 290, _T("���ڡ�JAVA��2��������ĵ�����������"));
	outtextxy(0, 350, _T("Ҳ��������������JAVA����MeniCreft��"));
	settextstyle(35, 10, _T("΢���ź�"));
	outtextxy(40, 420, _T("��JAVA��2�����Ͼɵļ��������˸��Ż�������ʹ���̳����֡������-60"));
	solidrectangle(800, 500, 1600, 570);
	settextstyle(55, 30, _T("΢���ź�"));
	outtextxy(950, 510, _T("���"));
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