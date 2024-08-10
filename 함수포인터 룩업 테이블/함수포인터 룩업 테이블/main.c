#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int para1;
	int para2;
	int para3;
}PARAS;

int (*g_opList[3])(PARAS*); // 함수 포인터 배열[3]선언 -> 가장빠른 룩업테이블

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

int main(int instNum, char** Insts) // 1 2 0 1 2 -> myfunc2,3,1,2,3 순서로 진행
{
	init_opList(); // 룩업테이블에 원하는 함수들 대입하는 초기화 과정

	PARAS paras = { 1,2,3 };
	
	volatile int instIdx = 1; // release 모드에선 이 변수가 삭제되어버림
	while (instIdx < instNum ) // 첫 인덱스는 함수의 이름이기에
	{
		int index = atoi(Insts[instIdx]);

		if(index >= 0 && index < 3)
			g_opList[index](&paras);
		
		instIdx++;
	}

	return 0;
}