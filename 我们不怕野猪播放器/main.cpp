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
		lrcs[i].str = ReadLine(".\\打野者.lrc", i).substr(10);
		minute = atoi(ReadLine(".\\打野者.lrc", i).substr(1, 3).c_str());
		second = atoi(ReadLine(".\\打野者.lrc", i).substr(4, 6).c_str());
		hsecond = atoi(ReadLine(".\\打野者.lrc", i).substr(7, 9).c_str());
		lrcs[i].hsecond = minute * 6000 + second * 100 + hsecond;
		cout << "[" << lrcs[i].hsecond << "]" << lrcs[i].str << endl;
		lrc[i] = lrcs[i];
	}
}
int main()
{
	int nowlrc = 0;
	SetConsoleTitle(_T("打野者"));
	SetWindowTextA(initgraph(800, 150, EW_SHOWCONSOLE), "打野者");
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setstyl(7, 24);
	outtextxy(0, 70, _T("该歌曲表达了作者对打野烈士英勇无畏的精神的敬重和赞美之情,对野猪卑鄙无耻"));
	outtextxy(0, 100, _T("的愤恨,以及对打野必将胜利、野猪必将失败的信心,呼吁人们一起打野"));
	setstyl(13, 60);
	outtextxy(40, 5, _T("打野者万岁！"));
	Sleep(4000);
	loadlrc();
	mciSendString(L"open 打野者.mp3", 0, 0, 0);
	mciSendString(L"play 打野者.mp3", 0, 0, 0);
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
