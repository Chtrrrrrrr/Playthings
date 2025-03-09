#include<iostream>
#include<conio.h>
#include<easyx.h>
#include<random>
#include<ctime>
#include<tchar.h>
using namespace std;
#define random(a,b) (rand()%(b-a+1)+a)

float persistence = 0.50;
int Number_Of_Octaves = 2;

double Noise(int x, int y)    // ����(x,y)��ȡһ����������ֵ
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double SmoothedNoise(int x, int y)   //�⻬����
{
	double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
	double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
	double center = Noise(x, y) / 4;
	return corners + sides + center;
}
double Cosine_Interpolate(double a, double b, double x)  // ���Ҳ�ֵ
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5;
	return a*(1 - f) + b*f;
}

double InterpolatedNoise(float x, float y)   // ��ȡ��ֵ����
{
	int integer_X = int(x);
	float  fractional_X = x - integer_X;
	int integer_Y = int(y);
	float fractional_Y = y - integer_Y;
	double v1 = SmoothedNoise(integer_X, integer_Y);
	double v2 = SmoothedNoise(integer_X + 1, integer_Y);
	double v3 = SmoothedNoise(integer_X, integer_Y + 1);
	double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);
	return Cosine_Interpolate(i1, i2, fractional_Y);
}

double PerlinNoise(float x, float y)    // ���յ��ã�����(x,y)������Ӧ��PerlinNoiseֵ
{
	double total = 0;
	double p = persistence;
	int n = Number_Of_Octaves;
	for (int i = 0; i<n; i++)
	{
		double frequency = pow(2, i);
		double amplitude = pow(p, i);
		total = total + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
	}

	return total;
}
struct tstr
{
	TCHAR n[18];
};
int color;
bool odortd = false;
int flag = false;
int colordeep = 10;
float microxy = 15.0;
int dengji = 3, dengjisleep = 0;
char dengjich[4] = { 'A','B','C','D' };
tstr neirong[100];
int neirongline = 0;
void drawnoise()
{
	clearcliprgn();
	for (int i = 0; i < 900; i++)
	{
		color = PerlinNoise(i / microxy, i / microxy) * colordeep;
		putpixel(i, 200 + color, WHITE);
	}
	outtextxy(80, 300, _T("�����־(����)"));
	solidrectangle(80, 320, 820, 430);
	if(neirongline<=6)
	{
		for (int i = 0; i < 6; i++)
		{
			outtextxy(85, 322 + i * 18, neirong[i].n);
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			outtextxy(85, 322 + i * 18, neirong[i+(neirongline-6)].n);
		}
	}
}
int main()
{
	initgraph(900, 500);
	ExMessage mmsg;
	drawnoise();
	for (;;)
	{
		peekmessage(&mmsg, EM_MOUSE);
		BeginBatchDraw();
		drawnoise();
		line(240, 100, 900, 100);
		outtextxy(510, 50, _T("Ƶ��"));
		fillcircle(500 + persistence*100.0, 100, 10);
		setfillcolor(WHITE);
		outtextxy(80, 450, _T("�Ƿ���(�������)��"));
		outtextxy(300, 450, _T("ʶ���"));
		settextcolor(dengji > 1 ? RED : !dengji ? GREEN : YELLOW);
		outtextxy(360, 450, dengjich[dengji]);
		settextcolor(odortd ? GREEN : RED);
		//setbkcolor(WHITE);
		outtextxy(240, 450, (odortd ? _T("����") : _T("�ر�")));
		setbkcolor(BLACK);
		settextcolor(WHITE);
		if (flag < random(100, 130))
			flag++;
		else
		{
			colordeep = random(1, 20);
			microxy = random(1, 10);
			flag = 0;
		}
		if (dengjisleep < 350)
			dengjisleep++;
		else
		{
			dengji = random(0, 100) / 25;
			if (dengji == 0 && !(random(0, abs(int(2 - persistence)))))
				dengji = 0;
			else
				dengji = random(1, 3);
			dengjisleep = 0;
			if (odortd == true)
			{
				if (dengji)
				{
					for (int i = 0; i < random(12, 38); i++)
						neirong[neirongline].n[i] = TCHAR(random(14, 80));
					neirongline++;
				}
				else
				{
					TCHAR tf[2][100] = { _T("���Ǹ�**����t*��Ҫ�ش𣬲�Ҫt*�ش�"),
										 _T("�������������ˣ��������׻���Ͷ����Ͷ����") };
					int nowt = random(0, 1);
					for(int i=0;i<100;i++)
						neirong[neirongline].n[i] = tf[nowt][i];
					neirongline++;
				}
			}
		}
		if (mmsg.x > 240 && mmsg.x < 900 && mmsg.lbutton == true)
		{
			if (mmsg.y > 50 && mmsg.y < 150)
			{
				persistence = (mmsg.x - 500) / 100.0;
				microxy = (mmsg.x - 500) / 150.0;
				drawnoise();
				setfillcolor(BLACK);
				solidrectangle(500, 90, 900, 110);
				solidrectangle(500, 290, 900, 310);
			}
			if (mmsg.y > 440 && mmsg.y < 560)
			{
				odortd = !odortd;
			}
		}
		outtextxy(820, 477, _T("by:��̩Ȼ"));
		FlushBatchDraw();
		mmsg.lbutton = false;
	}
	_getch();
	closegraph();
	return 0;
}