#include <Windows.h>

__declspec(naked) void main() // �� ������ naked Ư���� x86 Ư������ �۵��Ѵ�.
{
	char buff[5];

	buff[0] = 'c';
	buff[1] = 'a';
	buff[2] = 'l';
	buff[3] = 'c';
	buff[4] = 0;

	WinExec(buff, 1);
	exit(1);
}