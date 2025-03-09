#pragma once
#include <easyx.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <istream>
#include <ctime>
#include <sstream>
#include <mmsystem.h>
#include<dsound.h>
#include<iostream>
using namespace std;
//#pragma comment(lib, "WINMM.LIB")
#pragma comment(lib, "winmm.lib")
int GetTxtLine(const char *filename)

{
	FILE *fd;

	int count = 0;

	if (fd = fopen(filename, "r"))

	{
		while (!feof(fd))

		{
			if ('\n' == fgetc(fd))

			{
				count++;

			}

		}

	}

	printf("count: %d\n", count);

	if (fd)

	{
		fclose(fd);

	}

	return count;

}
std::string U8ToGB(const char* str)
{
	std::string result;
	WCHAR *strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}
string ReadLine(char *filename, int line)
{
	int i = 0;
	string temp;
	fstream file;
	file.open(filename, ios::in);

	if (line <= 0)
	{
		return "Error 1: 行数错误，不能为0或负数。";
	}

	if (file.fail())
	{
		return "Error 2: 文件不存在。";
	}

	while (getline(file, temp) && i<line - 1)
	{
		
		i++;
	}
	temp=U8ToGB(temp.c_str());
	file.close();
	return temp;
}
void setstyl(int tx, int ty)
{
		settextstyle(ty, tx, _T("华文行楷"));
}
BOOL StringToWString(const std::string &str, std::wstring &wstr)
{
	int nLen = (int)str.length();
	wstr.resize(nLen, L' ');

	int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

	if (nResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}std::string UTF8ToGB(const char* str)
{
	std::string result;
	WCHAR *strSrc;
	LPSTR szRes;
 
	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
 
	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
 
	result = szRes;
	delete[]strSrc;
	delete[]szRes;
 
	return result;
}