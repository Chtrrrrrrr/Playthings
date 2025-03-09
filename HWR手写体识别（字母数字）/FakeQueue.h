#pragma once

float ff[200] = { 0 };
bool ffb[200] = { false };
int nf=-1;
void push(float ft, bool bt)
{
	if (nf == 199)
	{
		for (int i = 0; i < 199; i++)
			ff[i] = ff[i + 1];
		ff[199] = ft;
		for (int i = 0; i < 199; i++)
			ffb[i] = ffb[i + 1];
		ffb[199] = bt;
	}
	if (nf < 199)
	{
		ff[++nf] = ft;
		ffb[nf] = bt;
	}
}