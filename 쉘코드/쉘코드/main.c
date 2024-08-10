#include <Windows.h>

__declspec(naked) void main() // 잘 모르지만 naked 특성은 x86 특성에서 작동한다.
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