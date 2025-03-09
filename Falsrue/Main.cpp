////////////////////////////////////////////
// �������դ��Ⱦһ�� 3D ��
// ���ߣ�����������־
// ���뻷����Visual Studio 2022��EasyX_20220901
// ��д���ڣ�2023-3-5

#include <graphics.h>
#include <math.h>
#include <vector>
#include <random>
#define RandomNumbers(a,b) (rand()%(b-a+1)+a)
const double PI = 3.1415926536; // ��
const int WIDTH = 640; 			// ��Ļ���
const int HEIGHT = 480; 		// ��Ļ�߶�
const int GAMEPAD = 60; 		// ��Ϸ�ֱ����ƶ����پ�����ת 60��
using std::vector;

// ��ά����
class Vec3
{
public:
	double xx, yy, zz;
	// ���캯��
	Vec3(double xx = 0, double yy = 0, double zz = 0) : xx(xx), yy(yy), zz(zz) {}
	// �������
	Vec3	operator+(Vec3 num) { return Vec3(this->xx + num.xx, this->yy + num.yy, this->zz + num.zz); }
	// �����˷�
	Vec3	operator*(double num) { return Vec3(this->xx * num, this->yy * num, this->zz * num); }
	// �������
	double	operator*(Vec3 num) { return this->xx * num.xx + this->yy * num.yy + this->zz * num.zz; }
	// ��������
	Vec3	operator/(double num) { return Vec3(this->xx / num, this->yy / num, this->zz / num); }
	// �������
	Vec3	operator-(Vec3 num) { return Vec3(this->xx - num.xx, this->yy - num.yy, this->zz - num.zz); }
	// �õ�������ģ��
	double	GetLength() { return sqrt(this->xx * this->xx + this->yy * this->yy + this->zz * this->zz); }
	// �õ�������֮��� cos ֵ
	double	GetCosBetween(Vec3 num) { return (*this) * num / this->GetLength() / num.GetLength(); }
	// �õ��������ĵ�λ����
	Vec3	GetUnitVector() { return (*this) / this->GetLength(); }
	// �õ�����������һ�������ϵ�ͶӰ
	Vec3	GetProjectionTo(Vec3 num) { return num.GetUnitVector() * (this->GetCosBetween(num) * this->GetLength()); }
	// �������
	Vec3	MultiplicationCross(Vec3 num) { return Vec3(this->yy * num.zz - this->zz * num.yy, -this->xx * num.zz + this->zz * num.xx, this->xx * num.yy - this->yy * num.xx); }
	// �󽫴��������� X �ᣬY �ᣬZ ����ת a��b��c �Ⱥ������
	Vec3	GetRotateVec(double a, double b, double c)
	{
		Vec3 result = this->GetUnitVector();
		result = Vec3(result.xx, result.yy * cos(a) - result.zz * sin(a), result.zz * cos(a) + result.yy * sin(a)).GetUnitVector();
		result = Vec3(result.xx * cos(b) - result.zz * sin(b), result.yy, result.zz * cos(b) + result.xx * sin(b)).GetUnitVector();
		result = Vec3(result.xx * cos(c) - result.yy * sin(c), result.yy * cos(c) + result.xx * sin(c), result.zz).GetUnitVector();
		return (result * this->GetLength());
	}
};

// ��ά����
class Vec2
{
public:
	double xx, yy;
	// ���캯��
	Vec2(double xx = 0, double yy = 0) : xx(xx), yy(yy) {}
	// �������
	Vec2	operator+(Vec2 num) { return Vec2(this->xx + num.xx, this->yy + num.yy); }
	// �����˷�
	Vec2	operator*(double num) { return Vec2(this->xx * num, this->yy * num); }
	// �������
	double	operator*(Vec2 num) { return this->xx * num.xx + this->yy * num.yy; }
	// ��������
	Vec2	operator/(double num) { return Vec2(this->xx / num, this->yy / num); }
	// �������
	Vec2	operator-(Vec2 num) { return Vec2(this->xx - num.xx, this->yy - num.yy); }
	// �õ�������ģ��
	double	GetLength() { return sqrt(this->xx * this->xx + this->yy * this->yy); }
	// �õ�������֮��� cos ֵ
	double	GetCosBetween(Vec2 num) { return (*this) * num / this->GetLength() / num.GetLength(); }
	// �õ��������ĵ�λ����
	Vec2	GetUnitVector() { return (*this) / this->GetLength(); }
	// �õ�����������һ�������ϵ�ͶӰ
	Vec2	GetProjectionTo(Vec2 num) { return num.GetUnitVector() * (this->GetCosBetween(num) * this->GetLength()); }
	// �õ���������ת angle �������
	Vec2	GetRotateVec(double angle) { return Vec2(this->xx * cos(angle) - this->yy * sin(angle), this->yy * cos(angle) + this->xx * sin(angle)); }
};

// ��ά������
class Triangle
{
public:
	Vec3 a, b, c;
	int H;
	// H �� 360 ��ֵ��ȡ
	// L 0~1 ���� cos ֵ����
	// ���캯��
	Triangle() = default;
	Triangle(Vec3 a, Vec3 b, Vec3 c, int H = 0) : a(a), b(b), c(c), H(H) {}
};

// �õ���ά�ռ��еĵ���ͶӰ���ϵ�ͶӰ
Vec2 GetProjectInSurface(Vec3 project, Vec3 X_Across, Vec3 Y_Across, Vec2 pericenter)	// �����ƽ��ͶӰ
{
	return pericenter +
		Vec2(project.GetLength() * project.GetCosBetween(X_Across),
			project.GetLength() * project.GetCosBetween(Y_Across));
}

// ��������ֵ
template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// �����������
void DrawTriangle(Triangle triangle, Vec3 X_Across, Vec3 Y_Across, Vec2 pericenter, double extent, double saturate = 1)
{
	if (extent < 0 || extent > 1) return;
	Vec2 a = GetProjectInSurface(triangle.a, X_Across, Y_Across, pericenter);
	Vec2 b = GetProjectInSurface(triangle.b, X_Across, Y_Across, pericenter);
	Vec2 c = GetProjectInSurface(triangle.c, X_Across, Y_Across, pericenter);
	POINT pointArr[3] = { {a.xx, a.yy}, {b.xx, b.yy }, {c.xx, c.yy} };
	setlinecolor(RGB(41,107,201));
	setlinestyle(PS_SOLID, 2);
	polygon(pointArr, 3);
	setlinecolor(RGB(178,250,255));
	circle(a.xx, a.yy, 3);
	circle(b.xx, b.yy, 3);
	circle(c.xx, c.yy, 3);
}

// ����˷�����ʵֻ������֮��һһ��Ӧ��˵õ���һ������
Vec3 MartixMultiple(Vec3 a, Vec3 b)
{
	return Vec3(a.xx * b.xx, a.yy * b.yy, a.zz * b.zz);
}

// ����ά�����εߵ���Ҳ���Ǵ���ά�����ι��� xoy ƽ�棬xoz ƽ�棬yoz ƽ��ԳƵ���һ����ά������
Triangle ReversedTriangle(Triangle input, Vec3 dir)
{
	return Triangle(MartixMultiple(input.a, dir), MartixMultiple(input.b, dir), MartixMultiple(input.c, dir), input.H);
}

// ��������������������������������radius �ǰ뾶��layers �ǲ�����������������ɸ�л��˹����������һ������������ɵ������������� 8 * 4^(layers) �������ͽӽ�һ�����
vector<Triangle> GenerateTriangleMesh(double radius, int layers)
{
	vector<Triangle> parent;
	vector<Triangle> child;
	parent.push_back(Triangle(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1)));
	for (int i = 0; i < layers; i++)
	{
		for (Triangle i : parent)
		{
			Vec3 a_b = (i.a + i.b).GetUnitVector();
			Vec3 a_c = (i.a + i.c).GetUnitVector();
			Vec3 b_c = (i.b + i.c).GetUnitVector();
			child.push_back(Triangle(i.a, a_b, a_c));
			child.push_back(Triangle(a_b, i.b, b_c));
			child.push_back(Triangle(a_c, b_c, i.c));
			child.push_back(Triangle(b_c, a_c, a_b));
		}
		parent = child;
		child.clear();
	}
	Vec2 beginDir(1, 0);
	for (Triangle& i : parent)
	{
		Triangle temp_1 = Triangle(i.a * radius, i.b * radius, i.c * radius);
		Triangle temp_2 = Triangle(i.a * radius, i.c * radius, i.b * radius);
		Triangle triArr[8] = { ReversedTriangle(temp_1, Vec3(1,  1,  1)), ReversedTriangle(temp_2, Vec3(-1,  1,  1)),
							   ReversedTriangle(temp_2, Vec3(1, -1,  1)), ReversedTriangle(temp_2, Vec3(1,  1, -1)),
							   ReversedTriangle(temp_1, Vec3(-1, -1,  1)), ReversedTriangle(temp_1, Vec3(1, -1, -1)),
							   ReversedTriangle(temp_1, Vec3(-1,  1, -1)), ReversedTriangle(temp_2, Vec3(-1, -1, -1)) };
		for (int index = 0; index < 8; index++)
		{
			double XNUM = (triArr[index].a.xx + triArr[index].b.xx + triArr[index].c.xx) / 3.0;
			double YNUM = (triArr[index].a.yy + triArr[index].b.yy + triArr[index].c.yy) / 3.0;
			Vec2 triVec(XNUM, YNUM);
			// ��� cos ֵ������ y �����ж��Ƿ���� -1 �Գ�
			double Cos_Tri = triVec.GetCosBetween(beginDir);
			if (triVec.yy < 0) // Cos_Tri ���� -1 �Գ�
				Cos_Tri = -(Cos_Tri + 2);
			triArr[index].H = 90 * (Cos_Tri + 3);
			triArr[index].a = triArr[index].a.GetRotateVec(PI / 4.0, PI / 4.0, PI / 4.0);
			triArr[index].b = triArr[index].b.GetRotateVec(PI / 4.0, PI / 4.0, PI / 4.0);
			triArr[index].c = triArr[index].c.GetRotateVec(PI / 4.0, PI / 4.0, PI / 4.0);
			child.push_back(triArr[index]);
		}
	}
	return child;
}

// �������϶�ʱ X �ᣬY ����� Y ����ת
Vec3 HorizontalRotate(Vec3 X_Across, Vec3 Y_Across, double angle)
{
	Vec3 Z_Across = X_Across.MultiplicationCross(Y_Across);
	X_Across = X_Across * cos(angle) + Z_Across * sin(angle);
	return X_Across.GetUnitVector();
}

// ��������϶�ʱ X �ᣬY ����� X ����ת
Vec3 VerticalRotate(Vec3 X_Across, Vec3 Y_Across, double angle)
{
	Vec3 Z_Across = X_Across.MultiplicationCross(Y_Across);
	Y_Across = Y_Across * cos(angle) + Z_Across * sin(angle);
	return Y_Across.GetUnitVector();
}

// �滭�����μ���
void DrawTriangleSet(vector<Triangle> triangleSet, Vec3 X_Across, Vec3 Y_Across, Vec2 pericenter,
	Vec3* lightsource = nullptr, double saturate = 1)
{
	Vec3 Z_Across = X_Across.MultiplicationCross(Y_Across);
	for (Triangle& tri : triangleSet)
	{
		Vec3 normalVec = (tri.b - tri.a).MultiplicationCross(tri.c - tri.a).GetUnitVector();
		double extent = normalVec * Z_Across;
		DrawTriangle(tri, X_Across, Y_Across, pericenter, max(normalVec * (*lightsource), 0), saturate);

	}
}

// ��ת��ά������
void RotateTriangle(Triangle& tri, double a, double b, double c)
{
	tri.a = tri.a.GetRotateVec(a, b, c);
	tri.b = tri.b.GetRotateVec(a, b, c);
	tri.c = tri.c.GetRotateVec(a, b, c);
}

// ��ת�����μ���
void RotateTriangleSet(vector<Triangle>& triSet, double a, double b, double c)
{
	for (Triangle& i : triSet)
	{
		RotateTriangle(i, a, b, c);
	}
}

// ������
int main()
{
	Vec3 X_Across(1, 0, 0), Y_Across(0, 1, 0);
	Vec3 lightSource(sqrt(3) / 3, -sqrt(3) / 3, sqrt(3) / 3);
	vector<Triangle> triangleMesh = GenerateTriangleMesh(400, 2.5);
	RotateTriangleSet(triangleMesh, PI / 4, PI / 4, PI / 4);
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
	bool isExit = false;
	bool isLPress = false, isRPress = false;
	double saturate = 1;
	Vec2 ori_L, ori_R;
	ExMessage msg;
	while (!isExit)
	{
		X_Across = HorizontalRotate(X_Across, Y_Across, -0.0003);
		Y_Across = VerticalRotate(X_Across, Y_Across, 0.0002);
		cleardevice();
		DrawTriangleSet(triangleMesh, X_Across, Y_Across, Vec2(45, 40), &lightSource, saturate);
		FlushBatchDraw();
	}
	return 0;
}

/*#include "GameHead.hpp"
#include <graphics.h>

int main()
{	// ��ʱ����������Դ

	AddFontResourceEx(".\\Resource\\Font.ttf", FR_PRIVATE, NULL);
	WindowHWND = initgraph(1200, 700);
	SetWindowTextW(WindowHWND, GameWindowTitle); //������
	CenterWindowF(WindowHWND); //���� 
	settextstyle(20, 0, "Unifont");	

	HDC WindowHDC = GetDC(WindowHWND);
	setbkmode(TRANSPARENT);
	SetGraphicsMode(WindowHDC, GM_ADVANCED);
	

	Loading();
	StartAni();
	Game();
	//ж��
	RemoveFontResourceEx(".\\Resource\\Font.ttf", FR_PRIVATE, NULL);
}*/