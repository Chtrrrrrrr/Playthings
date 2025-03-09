#include"head.h"

struct lr
{
	string str;
	int hsecond=0;
};
lr lrc[100];
time_t starttime;
long long stime=0;
int a, b, c, d;
void start()
{
	mciSendString(TEXT("open 我们不怕.wma alias mysong"), NULL, 0, NULL);
	mciSendString(TEXT("play mysong repeat"), NULL, 0, NULL);
	
}
void loadlrc()
{
	lr lrcs[100];
	int minute, second,hsecond;
	int lines= GetTxtLine((".\\我们不怕野猪.lrc"));
	for (int i = 1; i < 78; i++)
	{
		lrcs[i].str = ReadLine(".\\我们不怕.lrc", i).substr(10);
		minute = atoi(ReadLine(".\\我们不怕.lrc", i).substr(1, 3).c_str());
		second = atoi(ReadLine(".\\我们不怕.lrc", i).substr(4, 6).c_str());
		hsecond = atoi(ReadLine(".\\我们不怕.lrc", i).substr(7, 9).c_str());
		lrcs[i].hsecond = minute*1000 + second*100 + hsecond;
		cout << "[" << lrcs[i].hsecond << "]" << lrcs[i].str << endl;
		lrc[i] = lrcs[i];
	}
}
int main()
{
	int nowlrc = 0;
	SetWindowTextA(initgraph(800, 150, EW_SHOWCONSOLE), _T("我们不怕"));
	SetConsoleTitle(_T("我们不怕"));
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setstyl(20, 60);
	outtextxy(0, 30, _T("我们不怕"));
	loadlrc();
	start();
	cout << endl << endl << endl;
	wstring c;

	for (int i=0;i<32;i++)
	{
		c.clear();
		cleardevice();
		settextcolor(RED);
		StringToWString(lrc[nowlrc].str, c);
		outtextxy(10, 10, c.c_str());
		c.clear();
		settextcolor(BLACK);
		StringToWString(lrc[nowlrc+1].str, c);
		outtextxy(870-textwidth(c.c_str()), 90, c.c_str());
		cout << lrc[nowlrc].str << endl;
		Sleep((lrc[nowlrc+1].hsecond-lrc[nowlrc].hsecond)*10);
		nowlrc++;
	}
	Sleep(3330);
	for (int i = 32; i<44; i++)
	{
		c.clear();
		StringToWString(lrc[nowlrc].str, c);
		cleardevice();
		outtextxy(10, 30, c.c_str());
		cout << lrc[nowlrc].str << endl;
		Sleep(((lrc[nowlrc + 1].hsecond-10000) - (lrc[nowlrc].hsecond - 10000)) * 10);
		nowlrc++;
	}
	closegraph();
	return 0;
}
