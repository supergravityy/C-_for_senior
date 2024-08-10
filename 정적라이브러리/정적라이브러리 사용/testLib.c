#include <stdio.h>

#pragma comment(lib, "..\\x64\\Debug\\정적라이브러리.lib")
// 라이브러리의 종류와 위치를 알려줌

int Myadd(int a, int b)
{
	puts("add in exe\n");
	return a + b;
}

int add_in_Lib(int a, int b); // 원래는 헤더에다가 쓰는게 좀더 낫다

int main()
{
	Myadd(4, 5);
	add_in_Lib(5, 5);
	return 0;
}