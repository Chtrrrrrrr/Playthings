/*****************************************************************//**
 * \file   main.cpp
 * \brief  3D��Ⱦ����
 *		   ������������ϵ
 * \author Chtrrrrrrr
 * \date   January 2025
 *********************************************************************/
/*
	����ת��
				�����֡��Ȼ���˶��(W. Zaki Shude)
	��������������ȥ����������������Ҫ��
										�������󽫾�
*/
#include <iostream>
#include "windows.system.h"
#include <cstring>
#include <string>
#include <conio.h>
#include <cmath>
#include <easyx.h>

using namespace std;
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������
//�ڲ�����
#define MAXOBJECTFACES 100 //ÿ��������������С��������������
//const bool EFFICIENTMODE = true; //�Ƿ�������ģʽ����Ӱ���դ����������Ч��
const float INFINITED = 114514; //��������Զ
//����
const double PI = 3.1415926535897932384626433832795; //��
//�������
const int WindowWidth = 800, WindowHeight = 600; //�������
const int DefaultBkColor = WHITE; //Ĭ�ϱ�����ɫ
const int LamBda = 100; //���ű�������һ����λ�����Ӧ�����س�

//������������������������������������������������������������������������������������ʸ��������������������������������������������������������������������������������������
//��άʸ��
struct Vector
{
	float x; float y; float z;
	//���캯��
	inline Vector() : x(0), y(0), z(0) {};
	inline Vector(float X, float Y, float Z = 1) { x = X; y = Y; z = Z; }
	//���������
	Vector operator+(Vector v) { return Vector(x + v.x, y + v.y, z + v.z); } //�ӷ�
	Vector operator-(Vector v) { return Vector(x - v.x, y - v.y, z - v.z); } //�ӷ�
	Vector operator*(float k) { return Vector(x * k, y * k, z * k); }//����
	float operator*(Vector v) { return x * v.x + y * v.y + z * v.z; } //��� A �� B
	Vector operator%(Vector v) { return Vector(v.z * y - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y); } //��� A x B
	//ģ��
	inline float length() const { return sqrt(x * x + y * y + z * z); }
};

//��������������������������������������������������������������������������������������ĻͰ������������������������������������������������������������������������������������
//��Ļ�ռ�����飬������Ͱ�����õ�����
/*
����Ļ�ϵ�ÿһ���㣬ʹ��Ͱ�����˼�룬����
1.һ��ʼ�������ض���Ĭ�ϣ����붼������Զ
2.ÿ����һ����Face�������Σ���������Ƶ���Ļ�ռ��ʹ�����Բ�ֵ��������������еĵ㵽��ƽ��ľ��룬�Ҵ�������
3.�ڶ��������ڵ�ÿ�����ؼ���������õ��Ӧ��screen���������Ϣ�Ƚϣ�������ľ���С��ԭ��������ľ����Ҵ���0���滻��֮ǰ��
4.ѭ��������������ʱ��ֻ�����棬�����ƾ�������Զ���������Զ��޳��˿�����������
*/
//Vectorת��ɫ
static COLORREF Vector2Color(Vector v) { return RGB(v.x, v.y, v.z); }
//COLORREFתVector
static Vector Color2Vector(COLORREF c) { return Vector(GetRValue(c), GetGValue(c), GetBValue(c)); }
//��ĻͰ
struct PaneBuffer
{
	float distance = INFINITED; //����
	Vector color = Color2Vector(DefaultBkColor); //��ɫ��RGB����ά�ȣ�0-255
}Screen[WindowWidth][WindowHeight];

//����ĻͰ�������Ļ
//˳��������·�ת���Ե�������ϵy��
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
//���
void ClearSBuffer()
{
	for (int x = 0; x < WindowWidth; x++)
		for (int y = 0; y < WindowHeight; y++)
		{
			Screen[x][y].distance = INFINITED;
			Screen[x][y].color = Color2Vector(DefaultBkColor);
		}
}

//�������������������������������������������������������������������������������������ӡ�����������������������������������������������������������������������������������
//������꣬�����ڴ���ε����־
static string OutputVector(Vector v) {	return "Vector(three dimensional): x = " + to_string(v.x) + ", y = " + to_string(v.y) + ", z = " + to_string(v.z) + '\n'; }

//���������������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���
class camera
{
private:
	int Width = WindowWidth; //��ƽ���
	int Height = WindowHeight; //�ߣ�Ŀǰûɶ�ã�δ����׶�ü����ܻ�����
	float distance = 7; //�Ӿ� ����l
public:
	Vector location; //�ӵ��λ��
	float directionPHI = 0, directionTHETA = 0; //���߷����������ϵ��ʾ��Ҳ����ƽ��ķ�������thetaΪ��x������нǣ�phiΪ��xoyƽ��н�
	//���캯��
	camera() {};
	camera(float d) :distance(d) {}
	//���������굽��Ļ����
	Vector Global2Pane(Vector g)
	{
		Vector n = GetNormalVec();
		//1.��ȡ�õ�����ƽ���ϵ�ͶӰ����
		Vector b = (g - location) * ((distance*distance) / ((g - location) * n)) - n;
		//2.��ȡ��ƽ��Ļ�������3ά�е�����
		Vector i = Vector(-1.0 * sin(directionTHETA), cos(directionTHETA), 0);
		Vector j = (n % i)*(1.0/distance);
		//3.����ͶӰ������Ӧ����Ļ���꣬����z�������ڴ洢�õ㵽��Ļ�ľ���
		return Vector(b * i, b * j, (((g - location) * n)/distance)-distance);
	}
	//��ȡ��ƽ�淨���������ȴ������Ӿ���Ϣ��
	Vector GetNormalVec()
	{
		return Vector(distance * cos(directionPHI) * cos(directionTHETA), distance * cos(directionPHI) * sin(directionTHETA), distance * sin(directionPHI));
	}
}	;
//�������������������������������������������������������������������������������������桪����������������������������������������������������������������������������������
//�棨�����Σ�
class Face
{
private:
	Vector V[3]; //��������
	Vector Color; //�����ɫ
public: 
	//���캯��
	Face() {}
	Face(Vector v1, Vector v2, Vector v3, Vector c) :V{ v1,v2,v3 }, Color(c) {}
	//��Ⱦ����ĻͰ
	void Render2Buffer(camera ca)
	{
		Vector SV[3]; //ӳ�䵽��Ļ�ĵ�
		for (int i = 0; i < 3; i++) SV[i] = ca.Global2Pane(V[i]); //����ӳ��

	}
};

//�������������������������������������������������������������������������������������塪����������������������������������������������������������������������������������
//����
class Object
{
private:
	Face faces[MAXOBJECTFACES]; //����������������
public:


};

//������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
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

//���˺����㲻Ҫ������
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
				//���м򵥴ֱ�����Ұ���޳�
				if (i + j != 7 && Cube2[i].z * Cube2[j].z != 0)
					line(Cube2[i].x, Cube2[i].y, Cube2[j].x, Cube2[j].y);
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				//���м򵥴ֱ�����Ұ���޳�
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