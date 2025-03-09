#include <cstdio>
#include<iostream>
#include <windows.h>
using namespace std;
#define qdo 262
#define qre 294
#define qmi 330   //q前缀为低音，1后缀为高音，s前缀为半音阶
#define qfa 349
#define qso 392
#define qla 440
#define qxi 494
#define do 523
#define re 578
#define mi 659
#define fa 698
#define so 784
#define la 880
#define xi 988
#define do1 1046
#define re1 1175
#define mi1 1318
#define fa1 1480
#define so1 1568
#define la1 1760
#define xi1 1976
#define sqdo 277
#define sqre 311
#define sqfa 370
#define sqso 415
#define sqla 466
#define sdo 554
#define sre 622
#define sfa 740
#define sso 831
#define sla 932
#define sdo1 1046
#define sre1 1245
#define sfa1 1480
#define sso1 1661
#define sla1 1865
int main()
{
	Beep(so,300);
	Beep(la,300);
	Beep(so,300);
	Beep(fa,300);
	Beep(mi,300);
	Beep(re,600);
	Beep(do,1000);
	Beep(so,2000);
	Sleep(100);
	Beep(do,300);
	Beep(mi,300);
	Beep(do1,300);
	Beep(xi,300);
	Beep(la,600);
	Beep(mi,900);
	Beep(so,4000);
	Sleep(100);
	Beep(la,300);
	Beep(xi,300);
	Beep(la,300);
	Beep(so,300);
	Beep(fa,300);
	Beep(mi,350);
	Sleep(100);
	Beep(re,800);
	Beep(qla,800);
	Sleep(100);
	Beep(qxi,300);
	Beep(qla,300);
	Beep(qso,1000);
	Beep(so,300);
	Beep(do,2000);
	Beep(re,300);
	Beep(mi,4000);
	Sleep(100);
	Beep(so,300);
	Beep(la,300);
	Beep(so,300);
	Beep(fa,300);
	Beep(mi,300);
	Beep(re,600);
	Beep(do,1000);
	Beep(so,2000);
	Sleep(100);
	Beep(do,300);
	Beep(mi,300);
	Beep(do1,300);
	Beep(xi,300);
	Beep(re1,600);
	Beep(do1,900);
	Beep(la,4000);
	Sleep(100);
	Beep(do1,300);
	Beep(xi,300);
	Beep(la,300);
	Beep(so,700);
	Sleep(100);
	Beep(la,300);
	Beep(so,300);
	Beep(fa,300);
	Beep(mi,700);
	Sleep(100);
	Beep(qxi,300);
	Beep(qla,300);
	Beep(qso,300);
	Beep(re,500);
	Beep(do,1000);
	Sleep(100);
	Beep(do1,300);
	Beep(re1,300);
	Beep(mi1,300);
	Beep(re1,300);
	Beep(do1,300);
	Beep(la,300);
	Sleep(70);
	Beep(xi,600);
	Beep(la,300);
	Beep(mi,300);
	Beep(so,800);
	Sleep(70);
	Beep(do1,300);
	Beep(re1,300);
	Beep(mi1,300);
	Beep(re1,300);
	Beep(do1,300);
	Beep(la,300);
	Sleep(70);
	Beep(xi,300);
	Beep(so,600);
	Beep(mi,300);
	Beep(la,900);
	Sleep(70);
	Beep(so,300);
	Beep(fa,300);
	Beep(mi,300);
	Beep(re,800);
	Sleep(50);
	Beep(qxi,300);
	Beep(qla,300);
	Beep(qso,300);
	Beep(mi,800);
	Sleep(70);
	Beep(re1,300);
	return 0;
 }
