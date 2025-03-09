#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
	while(1)
	{
		char uerKey[1024] = "";
		printf("请输入要朗读的内容\n");
		gets(uerKey);
		FILE *fp = fopen("D:\\orange.vbs","w");
		fprintf(fp,"CreateObject(\"SAPI.SpVoice\").Speak(\"%s\")",uerKey);
		fclose(fp);
		system("D:\\orange.vbs");
		system("del D:\\orange.vbs");
	}
	system("pause");
	return 0;
}

