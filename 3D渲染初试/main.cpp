/*****************************************************************//**
 * \file   main.cpp
 * \brief  3D渲染初试
 *		   采用右手坐标系
 * \author Chtrrrrrrr
 * \date   January 2025
 *********************************************************************/
/*
	力大转飞
				——沃·兹基·硕德(W. Zaki Shude)
	高中生这样输下去，恐怕是连脸都不要了
										——范大将军
*/
#include <iostream>
#include "windows.system.h"
#include <cstring>
#include <string>
#include <conio.h>
#include <cmath>
#include <easyx.h>

using namespace std;
//——————————————————————————————————————————参数——————————————————————————————————————————
//内部参数
#define MAXOBJECTFACES 100 //每个物体的面数组大小，不想做链表了
//const bool EFFICIENTMODE = true; //是否开启性能模式，会影响光栅化的质量和效率
const float INFINITED = 114514; //近似无穷远
//常数
const double PI = 3.1415926535897932384626433832795; //π
//程序参数
const int WindowWidth = 800, WindowHeight = 600; //背景宽高
const int DefaultBkColor = WHITE; //默认背景颜色
const int LamBda = 100; //缩放倍数，即一个单位坐标对应几像素长

//——————————————————————————————————————————矢量——————————————————————————————————————————
//三维矢量
struct Vector
{
	float x; float y; float z;
	//构造函数
	inline Vector() : x(0), y(0), z(0) {};
	inline Vector(float X, float Y, float Z = 1) { x = X; y = Y; z = Z; }
	//运算符重载
	Vector operator+(Vector v) { return Vector(x + v.x, y + v.y, z + v.z); } //加法
	Vector operator-(Vector v) { return Vector(x - v.x, y - v.y, z - v.z); } //加法
	Vector operator*(float k) { return Vector(x * k, y * k, z * k); }//数乘
	float operator*(Vector v) { return x * v.x + y * v.y + z * v.z; } //点积 A · B
	Vector operator%(Vector v) { return Vector(v.z * y - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y); } //叉积 A x B
	//模长
	inline float length() const { return sqrt(x * x + y * y + z * z); }
};

//——————————————————————————————————————————屏幕桶——————————————————————————————————————————
//屏幕空间的数组，类似于桶排序用的数组
/*
对屏幕上的每一个点，使用桶排序的思想，即：
1.一开始所有像素都是默认，距离都是无穷远
2.每绘制一个面Face（三角形），等面绘制到屏幕空间后，使用线性插值计算这个面里所有的点到视平面的距离，且带有正负
3.在对三角形内的每个像素计算距离后，与该点对应的screen数组里的信息比较，如果他的距离小于原来数组里的距离且大于0，替换掉之前的
4.循环往复，最后绘制时，只绘制面，不绘制距离无穷远，这样就自动剔除了看不到的内容
*/
//Vector转颜色
static COLORREF Vector2Color(Vector v) { return RGB(v.x, v.y, v.z); }
//COLORREF转Vector
static Vector Color2Vector(COLORREF c) { return Vector(GetRValue(c), GetGValue(c), GetBValue(c)); }
//屏幕桶
struct PaneBuffer
{
	float distance = INFINITED; //距离
	Vector color = Color2Vector(DefaultBkColor); //颜色，RGB三个维度，0-255
}Screen[WindowWidth][WindowHeight];

//从屏幕桶输出到屏幕
//顺便进行上下反转，以调整坐标系y轴
void Render2Screen()
{
	for (int x = 0; x < WindowWidth; x++)
		for (int y = 0; y < WindowHeight; y++)
		{
			if (Screen[x][y].distance != INFINITED)
			{
				putpixel(x, WindowHeight - y, Vector2Color(Screen[x][y].color));
				//cout << "this!";
			}
		}
}
//清空
void ClearSBuffer()
{
	for (int x = 0; x < WindowWidth; x++)
		for (int y = 0; y < WindowHeight; y++)
		{
			Screen[x][y].distance = INFINITED;
			Screen[x][y].color = Color2Vector(DefaultBkColor);
		}
}

//——————————————————————————————————————————杂——————————————————————————————————————————
//输出坐标，可用于代码段点或日志
static string OutputVector(Vector v) {	return "Vector(three dimensional): x = " + to_string(v.x) + ", y = " + to_string(v.y) + ", z = " + to_string(v.z) + '\n'; }

//——————————————————————————————————————————相机——————————————————————————————————————————
//相机
class camera
{
private:
	int Width = WindowWidth; //视平面宽
	int Height = WindowHeight; //高，目前没啥用，未来视锥裁剪可能会有用
	float distance = 7; //视距 即：l
public:
	Vector location; //视点的位置
	float directionPHI = 0, directionTHETA = 0; //视线方向的球坐标系表示，也是视平面的法向量，theta为与x正方向夹角，phi为与xoy平面夹角
	//构造函数
	camera() {};
	camera(float d) :distance(d) {}
	//从世界坐标到屏幕坐标
	Vector Global2Pane(Vector g)
	{
		Vector n = GetNormalVec();
		//1.获取该点在视平面上的投影向量
		Vector b = (g - location) * ((distance*distance) / ((g - location) * n)) - n;
		//2.获取视平面的基向量在3维中的坐标
		Vector i = Vector(-1.0 * sin(directionTHETA), cos(directionTHETA), 0);
		Vector j = (n % i)*(1.0/distance);
		//3.返回投影向量对应的屏幕坐标，正好z坐标用于存储该点到屏幕的距离
		return Vector(b * i, b * j, (((g - location) * n)/distance)-distance);
	}
	//获取视平面法向量（长度储存了视距信息）
	Vector GetNormalVec()
	{
		return Vector(distance * cos(directionPHI) * cos(directionTHETA), distance * cos(directionPHI) * sin(directionTHETA), distance * sin(directionPHI));
	}
}	;
//——————————————————————————————————————————面——————————————————————————————————————————
//面（三角形）
class Face
{
private:
	Vector V[3]; //三个顶点
	Vector Color; //面的颜色
public: 
	//构造函数
	Face() {}
	Face(Vector v1, Vector v2, Vector v3, Vector c) :V{ v1,v2,v3 }, Color(c) {}
	//渲染到屏幕桶
	void Render2Buffer(camera ca)
	{
		Vector SV[3]; //映射到屏幕的点
		for (int i = 0; i < 3; i++) SV[i] = ca.Global2Pane(V[i]); //进行映射

	}
};

//——————————————————————————————————————————体——————————————————————————————————————————
//物体
class Object
{
private:
	Face faces[MAXOBJECTFACES]; //面数，懒得用链表
public:


};

//——————————————————————————————————————————主函数——————————————————————————————————————————
int main()
{
	//_getch();
	initgraph(WindowWidth, WindowHeight, 1);
	camera Ca(9);
	Ca.location = Vector(50, 0, 0);
	Ca.directionTHETA = PI;
	Ca.directionPHI = 0;
	cout << OutputVector(Ca.location);
	Face f1(Vector(5, 5, 5), Vector(5, 5, -5), Vector(5, -5, -5), Color2Vector(RED));
	Face f2(Vector(0, 5, -3), Vector(0, -7, -3), Vector(10, 4, 4), Color2Vector(BLUE));
	char c;
	for (;;)
	{
		ClearSBuffer();
		f1.Render2Buffer();
		f2.Render2Buffer();
		BeginBatchDraw();
		clearcliprgn();
		Render2Screen();
		FlushBatchDraw();
		c = _getch();
		/*switch (c)
		{
		case 's': {
			Ca.location = Ca.location - Ca.GetNormalVec(); break;
		}
		case 'w': {
			Ca.location = Ca.location + Ca.GetNormalVec(); break;
		}
		case 'a': {
			Ca.location = Ca.location - Vector(-Ca.GetNormalVec().y, Ca.GetNormalVec().x, 0); break;
		}
		case 'd': {
			Ca.location = Ca.location + Vector(-Ca.GetNormalVec().y, Ca.GetNormalVec().x, 0); break;
		}
		case 'j': {
			Ca.directionTHETA -= PI / 10; break;
		}
		case 'k': {
			Ca.directionPHI += PI / 10; break;
		}
		case 'l': {
			Ca.directionTHETA += PI / 10; break;
		}
		case 'i': {
			Ca.directionPHI -= PI / 10; break;
		}
		}*/
	}
	return 0;
}

//好了好了你不要再玩了
/*
int main()
{
	//_getch();
	initgraph(800, 600, 1);
	camera Ca;
	Ca.location = Vector(100, 50, 0);
	Ca.directionTHETA = PI;
	Ca.directionPHI = 0;
	//cout << OutputVector(Ca.Global2Pane(temp));
	Vector Cube[8] = { {1,1,1},{-1,1,1},{1,-1,1},{1,1,-1},{-1,-1,1},{-1,1,-1},{1,-1,-1},{-1,-1,-1}}; //except:
	Vector Cube2[8];
	Vector Cube3[8];
	Vector Cube4[8];
	Vector temp;
	float tx, ty;
	for (int i = 0; i < 8; i++)
	{
		Cube[i] = Cube[i] * 22.0;
	}
	for (int i = 0; i < 8; i++)
	{
		Cube3[i] = Cube[i] + Vector(0, 60, 0);
	}
	float e=0.00;
	char c;
	for (;;)
	{
		for (int i = 0; i < 8; i++)
		{
			tx = Cube[i].x; ty = Cube[i].y;
			Cube[i].x = cos(e) * tx - sin(e) * ty;
			Cube[i].y = cos(e) * ty + sin(e) * tx;
			Cube2[i] = Ca.Global2Pane(Cube[i]);
			Cube2[i] = Cube2[i] * 70 + Vector(400, 300, 0);
			cout << OutputVector(Cube[i]) << "|||" << OutputVector(Cube2[i]) << endl;
		}
		for (int i = 0; i < 8; i++)
		{
			tx = Cube3[i].x; ty = Cube3[i].y;
			Cube3[i].x = cos(e) * tx - sin(e) * ty;
			Cube3[i].y = cos(e) * ty + sin(e) * tx;
			Cube4[i] = Ca.Global2Pane(Cube3[i]);
			Cube4[i] = Cube4[i] * 70 + Vector(400, 300, 0);
			cout << OutputVector(Cube3[i]) << "|||" << OutputVector(Cube4[i]) << endl;
		}
		BeginBatchDraw();
		clearcliprgn();
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				//进行简单粗暴的视野后方剔除
				if (i + j != 7 && Cube2[i].z * Cube2[j].z != 0)
					line(Cube2[i].x, Cube2[i].y, Cube2[j].x, Cube2[j].y);
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				//进行简单粗暴的视野后方剔除
				if (i + j != 7 && Cube4[i].z * Cube4[j].z != 0)
					line(Cube4[i].x, Cube4[i].y, Cube4[j].x, Cube4[j].y);
			}
		}
		FlushBatchDraw();
		c=_getch();
		switch (c)
		{
		case 's': {Ca.location = Ca.location - Ca.GetNormalVec(); break;
		}
		case 'w': {Ca.location = Ca.location + Ca.GetNormalVec(); break;
		}
		case 'a':{Ca.location = Ca.location - Vector(-Ca.GetNormalVec().y, Ca.GetNormalVec().x, 0); break;
		}
		case 'd':{Ca.location = Ca.location + Vector(-Ca.GetNormalVec().y, Ca.GetNormalVec().x, 0); break;
		}
		case 'j':{Ca.directionTHETA -= PI / 10; break;
		}
		case 'k':{Ca.directionPHI += PI / 10; break;
		}
		case 'l':{Ca.directionTHETA += PI / 10; break;
		}
		case 'i':{Ca.directionPHI -= PI / 10; break;
		}
		}
		Sleep(10);
	}
	return 0;
}
*/