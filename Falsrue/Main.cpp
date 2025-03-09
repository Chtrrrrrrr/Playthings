////////////////////////////////////////////
// 程序：软光栅渲染一颗 3D 球
// 作者：我想做三国志
// 编译环境：Visual Studio 2022，EasyX_20220901
// 编写日期：2023-3-5

#include <graphics.h>
#include <math.h>
#include <vector>
#include <random>
#define RandomNumbers(a,b) (rand()%(b-a+1)+a)
const double PI = 3.1415926536; // π
const int WIDTH = 640; 			// 屏幕宽度
const int HEIGHT = 480; 		// 屏幕高度
const int GAMEPAD = 60; 		// 游戏手柄，移动多少距离旋转 60°
using std::vector;

// 三维向量
class Vec3
{
public:
	double xx, yy, zz;
	// 构造函数
	Vec3(double xx = 0, double yy = 0, double zz = 0) : xx(xx), yy(yy), zz(zz) {}
	// 向量相加
	Vec3	operator+(Vec3 num) { return Vec3(this->xx + num.xx, this->yy + num.yy, this->zz + num.zz); }
	// 向量乘法
	Vec3	operator*(double num) { return Vec3(this->xx * num, this->yy * num, this->zz * num); }
	// 向量点乘
	double	operator*(Vec3 num) { return this->xx * num.xx + this->yy * num.yy + this->zz * num.zz; }
	// 向量除法
	Vec3	operator/(double num) { return Vec3(this->xx / num, this->yy / num, this->zz / num); }
	// 向量相减
	Vec3	operator-(Vec3 num) { return Vec3(this->xx - num.xx, this->yy - num.yy, this->zz - num.zz); }
	// 得到此向量模长
	double	GetLength() { return sqrt(this->xx * this->xx + this->yy * this->yy + this->zz * this->zz); }
	// 得到两向量之间的 cos 值
	double	GetCosBetween(Vec3 num) { return (*this) * num / this->GetLength() / num.GetLength(); }
	// 得到此向量的单位向量
	Vec3	GetUnitVector() { return (*this) / this->GetLength(); }
	// 得到此向量在另一个向量上的投影
	Vec3	GetProjectionTo(Vec3 num) { return num.GetUnitVector() * (this->GetCosBetween(num) * this->GetLength()); }
	// 向量叉乘
	Vec3	MultiplicationCross(Vec3 num) { return Vec3(this->yy * num.zz - this->zz * num.yy, -this->xx * num.zz + this->zz * num.xx, this->xx * num.yy - this->yy * num.xx); }
	// 求将此向量关于 X 轴，Y 轴，Z 轴旋转 a、b、c 度后的向量
	Vec3	GetRotateVec(double a, double b, double c)
	{
		Vec3 result = this->GetUnitVector();
		result = Vec3(result.xx, result.yy * cos(a) - result.zz * sin(a), result.zz * cos(a) + result.yy * sin(a)).GetUnitVector();
		result = Vec3(result.xx * cos(b) - result.zz * sin(b), result.yy, result.zz * cos(b) + result.xx * sin(b)).GetUnitVector();
		result = Vec3(result.xx * cos(c) - result.yy * sin(c), result.yy * cos(c) + result.xx * sin(c), result.zz).GetUnitVector();
		return (result * this->GetLength());
	}
};

// 二维向量
class Vec2
{
public:
	double xx, yy;
	// 构造函数
	Vec2(double xx = 0, double yy = 0) : xx(xx), yy(yy) {}
	// 向量相加
	Vec2	operator+(Vec2 num) { return Vec2(this->xx + num.xx, this->yy + num.yy); }
	// 向量乘法
	Vec2	operator*(double num) { return Vec2(this->xx * num, this->yy * num); }
	// 向量点乘
	double	operator*(Vec2 num) { return this->xx * num.xx + this->yy * num.yy; }
	// 向量除法
	Vec2	operator/(double num) { return Vec2(this->xx / num, this->yy / num); }
	// 向量相减
	Vec2	operator-(Vec2 num) { return Vec2(this->xx - num.xx, this->yy - num.yy); }
	// 得到此向量模长
	double	GetLength() { return sqrt(this->xx * this->xx + this->yy * this->yy); }
	// 得到两向量之间的 cos 值
	double	GetCosBetween(Vec2 num) { return (*this) * num / this->GetLength() / num.GetLength(); }
	// 得到此向量的单位向量
	Vec2	GetUnitVector() { return (*this) / this->GetLength(); }
	// 得到此向量在另一个向量上的投影
	Vec2	GetProjectionTo(Vec2 num) { return num.GetUnitVector() * (this->GetCosBetween(num) * this->GetLength()); }
	// 得到此向量旋转 angle 后的向量
	Vec2	GetRotateVec(double angle) { return Vec2(this->xx * cos(angle) - this->yy * sin(angle), this->yy * cos(angle) + this->xx * sin(angle)); }
};

// 三维三角形
class Triangle
{
public:
	Vec3 a, b, c;
	int H;
	// H 有 360 个值可取
	// L 0~1 根据 cos 值决定
	// 构造函数
	Triangle() = default;
	Triangle(Vec3 a, Vec3 b, Vec3 c, int H = 0) : a(a), b(b), c(c), H(H) {}
};

// 得到三维空间中的点在投影面上的投影
Vec2 GetProjectInSurface(Vec3 project, Vec3 X_Across, Vec3 Y_Across, Vec2 pericenter)	// 这个是平行投影
{
	return pericenter +
		Vec2(project.GetLength() * project.GetCosBetween(X_Across),
			project.GetLength() * project.GetCosBetween(Y_Across));
}

// 交换两个值
template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// 画填充三角形
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

// 矩阵乘法，其实只是向量之间一一对应相乘得到另一个向量
Vec3 MartixMultiple(Vec3 a, Vec3 b)
{
	return Vec3(a.xx * b.xx, a.yy * b.yy, a.zz * b.zz);
}

// 将三维三角形颠倒，也就是此三维三角形关于 xoy 平面，xoz 平面，yoz 平面对称的另一个三维三角形
Triangle ReversedTriangle(Triangle input, Vec3 dir)
{
	return Triangle(MartixMultiple(input.a, dir), MartixMultiple(input.b, dir), MartixMultiple(input.c, dir), input.H);
}

// 生成三角网，根据球面生成三角网，radius 是半径，layers 是层数，这个三角网生成跟谢宾斯基三角形有一点点像，最终生成的三角网数量是 8 * 4^(layers) 个，五层就接近一万个了
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
			// 求得 cos 值，根据 y 正负判断是否关于 -1 对称
			double Cos_Tri = triVec.GetCosBetween(beginDir);
			if (triVec.yy < 0) // Cos_Tri 关于 -1 对称
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

// 鼠标横向拖动时 X 轴，Y 轴关于 Y 轴旋转
Vec3 HorizontalRotate(Vec3 X_Across, Vec3 Y_Across, double angle)
{
	Vec3 Z_Across = X_Across.MultiplicationCross(Y_Across);
	X_Across = X_Across * cos(angle) + Z_Across * sin(angle);
	return X_Across.GetUnitVector();
}

// 鼠标竖向拖动时 X 轴，Y 轴关于 X 轴旋转
Vec3 VerticalRotate(Vec3 X_Across, Vec3 Y_Across, double angle)
{
	Vec3 Z_Across = X_Across.MultiplicationCross(Y_Across);
	Y_Across = Y_Across * cos(angle) + Z_Across * sin(angle);
	return Y_Across.GetUnitVector();
}

// 绘画三角形集合
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

// 旋转三维三角形
void RotateTriangle(Triangle& tri, double a, double b, double c)
{
	tri.a = tri.a.GetRotateVec(a, b, c);
	tri.b = tri.b.GetRotateVec(a, b, c);
	tri.c = tri.c.GetRotateVec(a, b, c);
}

// 旋转三角形集合
void RotateTriangleSet(vector<Triangle>& triSet, double a, double b, double c)
{
	for (Triangle& i : triSet)
	{
		RotateTriangle(i, a, b, c);
	}
}

// 主函数
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
{	// 临时加载字体资源

	AddFontResourceEx(".\\Resource\\Font.ttf", FR_PRIVATE, NULL);
	WindowHWND = initgraph(1200, 700);
	SetWindowTextW(WindowHWND, GameWindowTitle); //标题栏
	CenterWindowF(WindowHWND); //居中 
	settextstyle(20, 0, "Unifont");	

	HDC WindowHDC = GetDC(WindowHWND);
	setbkmode(TRANSPARENT);
	SetGraphicsMode(WindowHDC, GM_ADVANCED);
	

	Loading();
	StartAni();
	Game();
	//卸载
	RemoveFontResourceEx(".\\Resource\\Font.ttf", FR_PRIVATE, NULL);
}*/