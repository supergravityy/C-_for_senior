#include <stdio.h>

#pragma comment(lib, "..\\x64\\Debug\\�������̺귯��.lib") 
__declspec(dllimport) int add_in_dll(int, int);

int main()
{
	add_in_dll(3, 4);
	return;
}