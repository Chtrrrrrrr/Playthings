#include<iostream>
#include<cmath>
#include<conio.h>
#include<easyx.h>
using namespace std;

int Input[202][202] = { 0 }; //源图像 RGB
float Output[200][200] = { 0 }; //池化层后
float Convolution[3][3] = { 0 }; //卷积核
int OutputX = 200, OutputY = 200;//(W-F+2P/S)+1      源x/y-卷积核x/y+边缘填充*2➗步长 +1
int main() {
	IMAGE ph;
	loadimage(&ph, _T(".\\photo.png")); //输入卷积核内容
	cout<< "卷积核内容(3x3(单色通道)):" <<endl;
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			cin >> Convolution[x][y];//读取源图像内容
	initgraph(800, 800); //创建窗口
	setbkcolor(WHITE); //白色背景
	clearcliprgn(); //刷新背景
	putimage(51, 51, &ph); //显示图片
	for (int x = 51; x < 251; x++) //读取像素值，由于黑白照片RGB单通道值相等，所以这里取R通道值
		for (int y = 51; y < 251; y++) {
			Input[x - 50][y - 50] = GetRValue(getpixel(x, y)); //R
		}
	//开始卷积
	for (int x = 0; x < OutputX; x++)
		for (int y = 0; y < OutputY; y++)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					Output[x][y] += Convolution[i][j] * Input[x + i][y + j];
	for (int x = 255; x < 455; x++)
		for (int y = 51; y < 251; y++)
			putpixel(x, y, RGB(Output[x - 255][y - 51], Output[x - 255][y - 51], Output[x - 255][y - 51]));
	_getch();
	closegraph();
	return 0;
}
/*#include<iostream>
#include<cmath>
#include<conio.h>
#include<easyx.h>
using namespace std;

double sigmoid(double x)
{
	if (x > 0)
		return 1.0 / (1.0 + exp(-x));
	else
		return exp(x) / (1.0 + exp(x));
}
	
int Input[3][202][202] = { 0 }; //源图像 RGB
float Convolution[3][3][3] = { 0 }; //卷积核
float Bais; //偏置值
float Output[200][200] = { 0 }; //特征图
float Output_MaxPooling[100][100] = { 0 }; //池化层后
int OutputX=200, OutputY=200;//(W-F+2P/S)+1      源x/y-卷积核x/y+边缘填充*2➗步长 +1
int main()
{
	IMAGE ph;
	loadimage(&ph, _T(".\\photo.png"));
	//输入卷积核内容
	cout << "卷积核内容(3x3x3(RGB通道)):" << endl;
	for (int z = 0; z < 3; z++)
	{
		cout << "第" << z << "层" << endl;
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
				cin >> Convolution[z][x][y];
	}
	//输入偏置值
	cout << "偏置值:" << endl;
	cin >> Bais;
	//读取源图像内容
	initgraph(800,800);
	setbkcolor(WHITE);
	clearcliprgn();
	putimage(51, 51, &ph);
	for (int x = 51; x < 251; x++)
		for (int y = 51; y < 251; y++)
		{
			Input[0][x - 50][y - 50] = GetRValue(getpixel(x, y)); //R
			Input[1][x - 50][y - 50] = GetGValue(getpixel(x, y)); //G
			Input[2][x - 50][y - 50] = GetBValue(getpixel(x, y)); //B
		}
	//output
	for (int x = 0; x < 202; x++)
		for (int y = 250; y < 452; y++)
			putpixel(x, y, RGB(Input[0][x][y - 250],0,0));
	for (int x = 100; x < 302; x++)
		for (int y = 250; y < 452; y++)
			putpixel(x, y, RGB(0,Input[1][x - 100][y - 250],0));
	for (int x = 200; x < 402; x++)
		for (int y = 250; y < 452; y++)
			putpixel(x, y, RGB(0,0,Input[2][x - 200][y - 250]));
	//开始卷积
	for (int z = 0; z < 3; z++)
		for (int x = 0; x < OutputX; x++)
			for (int y = 0; y < OutputY; y++)
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						Output[x][y] += Convolution[z][i][j] * Input[z][x + i][y + j];
	for (int x = 0; x < OutputX; x++) //偏置值
		for (int y = 0; y < OutputY; y++)
			Output[x][y] += Bais;
	//将特征图信息压缩到可显示范围内
	float Output_Max = 0;
	for (int x = 0; x < OutputX; x++) //取最大值
		for (int y = 0; y < OutputY; y++)
			if (Output[x][y] > Output_Max)
				Output_Max = Output[x][y];
	float temp = Output_Max >= 255 ? 255.0 / Output_Max : 1;
	for (int x = 0; x < 200; x++)
		for (int y = 500; y < 700; y++)
			putpixel(x, y, RGB(sigmoid(Output[x][y - 500]) * 255.0, sigmoid(Output[x][y - 500]) * 255.0, sigmoid(Output[x][y - 500]) * 255.0));
	//池化层(max pooling)
	int tmp = 0;
	for (int x = 0, x1 = 0; x1 < OutputX; x++, x1 += 2)
		for (int y = 0, y1 = 0; y1 < OutputY; y++, y1 += 2)
		{
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					if (Output[x1 + i][y1 + j] > tmp)
						tmp = Output[x1 + i][y1 + j];
			Output_MaxPooling[x][y] = tmp;
			tmp = 0;
		}
	//输出
	for (int x = 250; x < 350; x++)
		for (int y = 500; y < 600; y++)
			putpixel(x, y, RGB(Output_MaxPooling[x - 250][y - 500] * temp, Output[x - 250][y - 500] * temp, Output[x - 250][y - 500] * temp));
	_getch();
	closegraph();
	return 0;
}*/