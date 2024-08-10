#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int para1;
	int para2;
	int para3;
}PARAS;

int (*g_opList[3])(PARAS*); // �Լ� ������ �迭[3]���� -> ������� ������̺�

int Myfunc1(PARAS* paras)
{
	printf("Myfunc1\nParameter : %d, %d, %d\n", paras->para1, paras->para2, paras->para3);
	return 0;
}

int Myfunc2(PARAS* paras)
{
	printf("Myfunc2\nParameter : %d, %d, %d\n", paras->para1, paras->para2, paras->para3);
	return 0;
}

int Myfunc3(PARAS* paras)
{
	printf("Myfunc3\nParameter : %d, %d, %d\n",paras->para1,paras->para2,paras->para3);
	return 0;
}

void init_opList()
{
	g_opList[0] = Myfunc1;
	g_opList[1] = Myfunc2;
	g_opList[2] = Myfunc3;
}

int main(int instNum, char** Insts) // 1 2 0 1 2 -> myfunc2,3,1,2,3 ������ ����
{
	init_opList(); // ������̺� ���ϴ� �Լ��� �����ϴ� �ʱ�ȭ ����

	PARAS paras = { 1,2,3 };
	
	volatile int instIdx = 1; // release ��忡�� �� ������ �����Ǿ����
	while (instIdx < instNum ) // ù �ε����� �Լ��� �̸��̱⿡
	{
		int index = atoi(Insts[instIdx]);

		if(index >= 0 && index < 3)
			g_opList[index](&paras);
		
		instIdx++;
	}

	return 0;
}