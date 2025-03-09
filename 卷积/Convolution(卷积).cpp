/*#include<iostream>
#include<cmath>
using namespace std;

float Input[100][100] = { 0 }; //源图像
int InputX, InputY; //源图像大小
float Convolution[3][3] = { 0 }; //卷积核
float Bais; //偏置值
float Output[100][100] = { 0 }; //特征图
int OutputX, OutputY;//(W-F+2P/S)+1      源x/y-卷积核x/y+边缘填充*2➗步长 +1
int main()
{
	//输入边缘填充宽度
	cout << "边缘填充宽度:" << endl;
	int Pad;
	cin >> Pad;
	//输入源图像内容
	cout << "源图像大小:" << endl;
	cin >> InputX >> InputY;
	cout << "源图像内容:" << endl;
	for (int x = 0 + Pad; x < InputX + Pad; x++)
		for (int y = 0 + Pad; y < InputY + Pad; y++)
			cin >> Input[x][y];
	//输入卷积核内容
	cout << "卷积核内容(3x3):" << endl;
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			cin >> Convolution[x][y];
	//输入偏置值
	cout << "偏置值:" << endl;
	cin >> Bais;
	//特征图边长
	OutputX = 1 + ((InputX - 3 + 2 * Pad) / 1);
	OutputY = 1 + ((InputY - 3 + 2 * Pad) / 1);
	//开始卷积
	for (int x = 0; x < OutputX; x++)
		for (int y = 0; y < OutputY; y++)
		{
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					Output[x][y] += Convolution[i][j] * Input[x + i][y + j];
				}
			Output[x][y] += Bais;
		}
	//输出
	cout << "源图像:" << endl;
	for (int x = 0; x < InputX + 2 * Pad; x++)
	{
		for (int y = 0; y < InputY + 2 * Pad; y++)
			cout << Input[x][y]<<" ";
		cout << endl;
	}
	cout << "卷积核:" << endl;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
			cout << Convolution[x][y] << " ";
		cout << endl;
	}
	cout << "边缘填充" << Pad << "行0" << endl;
	cout << "偏置值:" << Bais << endl;
	cout << "特征图" << endl;
	for (int x = 0; x < OutputX; x++)
	{
		for (int y = 0; y < OutputY; y++)
			cout << Output[x][y] << " ";
		cout << endl;
	}
	return 0;
}*/