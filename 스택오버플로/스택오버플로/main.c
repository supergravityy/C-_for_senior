#include <stdio.h>

__declspec(naked) void overrunTest()
{
	puts("stack overrun!");
}

void Targetfunc(int param)
{
	puts("targetfunc-called");
	int local = 10;
	*(&local + 2) = (int)overrunTest;
	puts("targetfunc-returned");
}

void main()
{
	puts("begin");
	Targetfunc(0);
	puts("end");
}