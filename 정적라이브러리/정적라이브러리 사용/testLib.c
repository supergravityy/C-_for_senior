#include <stdio.h>

#pragma comment(lib, "..\\x64\\Debug\\�������̺귯��.lib")
// ���̺귯���� ������ ��ġ�� �˷���

int Myadd(int a, int b)
{
	puts("add in exe\n");
	return a + b;
}

int add_in_Lib(int a, int b); // ������ ������ٰ� ���°� ���� ����

int main()
{
	Myadd(4, 5);
	add_in_Lib(5, 5);
	return 0;
}