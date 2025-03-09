#pragma once
#include "Head.hpp"
#include "RrConfig.h"
#include <thread>
#include <mutex> 

mutex MTX;
bool IsLoadThreadFinished = false;
//加载线程
void LoadThread()
{
	loadimage(&ClearIMAGE, ".\\Resource\\Map\\Clear.png");
	MTX.lock();
	IsLoadThreadFinished = true;
	MTX.unlock();
}
void Loading()
{
	IMAGE LoadingIMG, LoadingBackground, Start,LoadingIMG2,AniIMAGE(984,180),Falsrue;
	loadimage(&LoadingIMG, ".\\Resource\\Loading.png");
	loadimage(&LoadingBackground, ".\\Resource\\LoadingBackground.png");
	loadimage(&Falsrue, ".\\Resource\\Falsrue.png");
	//背景下滑
	thread Load(LoadThread);
	Load.detach();
	for (int y = -800; y <= 0; y += 5)
	{ 
		BeginBatchDraw();
		TransparentIMAGE(NULL, 0, y, &LoadingBackground);
		TransparentIMAGE(NULL, 0, 0, &LoadingIMG);
		if (y >= -447)
		{
			if (y <= -267)
			{
				AniIMAGE.Resize(984, y + 447);
				TransparentIMAGE(&AniIMAGE, 0, 0, &Falsrue);
				TransparentIMAGE(NULL, 112, 256, &AniIMAGE);
			}
			else
				TransparentIMAGE(NULL, 112, 256, &Falsrue);
		}
		FlushBatchDraw();
		Sleep(5);
	}
	//等待加载完成
	while (true)
	{
		MTX.lock(); 
		if (IsLoadThreadFinished) { MTX.unlock(); break; }
		MTX.unlock();
	}
	setbkcolor(RGB(38, 38, 38));
	cleardevice();
	loadimage(&Start, ".\\Resource\\Start.png");
	loadimage(&LoadingIMG2, ".\\Resource\\Loading2.png");
	//“Loading...”淡出
	for (BYTE i = 255; i >= 1; i -= 15)
	{
		cleardevice();
		TransparentIMAGE(NULL, 0, 0, &LoadingIMG, i);
		TransparentIMAGE(NULL, 0, 0, &LoadingIMG2);
		TransparentIMAGE(NULL, 112, 256, &Falsrue);
		FlushBatchDraw();
		Sleep(1);
	}
	//“按任意键继续”向上划入（等待一会）
	loadimage(&LoadingIMG, ".\\Resource\\Loading3.png");
	for (int i = 1000; i >= 500; i-=20)
	{
		TransparentIMAGE(NULL, 0, 0, &LoadingIMG);
		TransparentIMAGE(NULL, 420, i, &Start);
		FlushBatchDraw();
		Sleep(1);
	}
	_getch();
	//淡出，“按任意键继续”向下划出
	int temp = 500;
	for (BYTE i = 255; i >= 1; i -= 5,temp+=30)
	{
		cleardevice();
		TransparentIMAGE(NULL, 0, 0, &LoadingIMG, i);
		TransparentIMAGE(NULL, 420, temp, &Start);
		FlushBatchDraw();
		Sleep(1);
	}
	EndBatchDraw();
	cleardevice();
}
void StartAni()
{
	rr::RrConfig InitFile;
	InitFile.ReadConfig(".\\Resource\\Game.ini.txt");
	StartDialog:
	if (GetPrivateProfileInt("GameInit", "HaveStarted", 0, ".\\Resource\\Game.ini"))
	{
		if (DialogOutput(1, 600, 350, 35, WHITE) == 'c')
		{
			if (DialogOutput(2, 600, 350, 35, WHITE) == 'c')
			{
				WritePrivateProfileString("GameInit", "HaveStarted", "0", ".\\Resource\\Game.ini");
				exit(0);
			}
			else
				goto StartDialog;
		}
		else
			DialogOutput(3, 600, 350, 35, WHITE);
	}
	else
	{
		DialogOutput(0, 600, 350, 35, WHITE);
		WritePrivateProfileString("GameInit", "HaveStarted", "1", ".\\Resource\\Game.ini");
	}
}
//窗口渲染线程
void WindowOutputThread()
{
	cleardevice();
	for (int i=0;;i++)
	{
		WindowCanvasClear();
		BeginBatchDraw();
		WindowCanvasOutput();
		settextcolor(BLACK);
		outtextxy(0, 0, to_string(i).c_str());
		FlushBatchDraw();
	}
}
//内容渲染线程
void OutputThread()
{

}
//操作线程
void ControlThread()
{
	for (;;)
	{

	}
}
void Game()
{
	thread WindowOutput(WindowOutputThread);
	thread Output(OutputThread);
	thread Control(ControlThread);
	WindowOutput.detach();
	Output.detach();
	Control.detach();
	while (true);
}