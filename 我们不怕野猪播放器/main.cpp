#include"head.h"

struct lr
{
	string str;
	int hsecond = 0;
};
lr lrc[100];
time_t starttime;
long long stime = 0;
int a, b, c, d;
void start()
{
}
void loadlrc()
{
	lr lrcs[100];
	int minute, second, hsecond;
	for (int i = 1; i < 72; i++)
	{
		lrcs[i].str = ReadLine(".\\��Ұ��.lrc", i).substr(10);
		minute = atoi(ReadLine(".\\��Ұ��.lrc", i).substr(1, 3).c_str());
		second = atoi(ReadLine(".\\��Ұ��.lrc", i).substr(4, 6).c_str());
		hsecond = atoi(ReadLine(".\\��Ұ��.lrc", i).substr(7, 9).c_str());
		lrcs[i].hsecond = minute * 6000 + second * 100 + hsecond;
		cout << "[" << lrcs[i].hsecond << "]" << lrcs[i].str << endl;
		lrc[i] = lrcs[i];
	}
}
int main()
{
	int nowlrc = 0;
	SetConsoleTitle(_T("��Ұ��"));
	SetWindowTextA(initgraph(800, 150, EW_SHOWCONSOLE), "��Ұ��");
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setstyl(7, 24);
	outtextxy(0, 70, _T("�ø�����������߶Դ�Ұ��ʿӢ����η�ľ���ľ��غ�����֮��,��Ұ�����޳�"));
	outtextxy(0, 100, _T("�ķߺ�,�Լ��Դ�Ұ�ؽ�ʤ����Ұ��ؽ�ʧ�ܵ�����,��������һ���Ұ"));
	setstyl(13, 60);
	outtextxy(40, 5, _T("��Ұ�����꣡"));
	Sleep(4000);
	loadlrc();
	mciSendString(L"open ��Ұ��.mp3", 0, 0, 0);
	mciSendString(L"play ��Ұ��.mp3", 0, 0, 0);
	cout << endl << endl << endl;
	wstring c;
	int sleeptime = 0;
	for (int i = 0; i<78; i++)
	{
		cleardevice();
		sleeptime = (lrc[nowlrc + 1].hsecond - lrc[nowlrc].hsecond) * 10;
		c.clear();
		settextcolor(BLACK);
		StringToWString(lrc[nowlrc + 1].str, c);
		outtextxy(855 - textwidth(c.c_str()), 90, c.c_str());
		cout << lrc[nowlrc].str << endl;
		c.clear();
		StringToWString(lrc[nowlrc].str, c);
		outtextxy(10, 10, c.c_str());
		settextcolor(RED);
		for (int i = 0; i < c.length(); i++)
		{
			outtextxy(10, 10, c.substr(0,i).c_str());
			Sleep(sleeptime / c.length());
		}
		nowlrc++;
	}
	closegraph();
	return 0;
}
