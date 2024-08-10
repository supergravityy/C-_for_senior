#include <Windows.h>

void main() // 이전 어셈블리 코드를 hxD 혹은 메모리 창에서 봐서 코드만큼의 기계어를 직접 타이핑
{
	char shellcode[] = "\x55\x8B\xEC\x83\xEC\x48"
		"\xC6\x45\xF4\x63\xC6\x45\xF5\x61\xC6"
		"\x45\xF6\x6C\xC6\x45\xF7\x63\xC6\x45"
		"\xF8\x00\x6A\x01\x8D\x45\xF4\x50\xA1"
		"\x00\x70\x41\x00\xFF\xD0\x6A\x01\xA1"
		"\xC0\x70\x41\x00\xFF\xD0";
	//	WinExec("", 0);
	//	exit(0);
	int* pShell = (int*)shellcode; 
	// x86 아키텍처를 노리고 쓴 것이기 때문에 이렇다. -> 포인터 주소가 4바이트이기에 배열의 시작주소로 점프
	__asm
	{
		jmp	pShell
	}
}