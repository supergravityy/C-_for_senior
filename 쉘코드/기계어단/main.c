#include <Windows.h>

void main() // ���� ����� �ڵ带 hxD Ȥ�� �޸� â���� ���� �ڵ常ŭ�� ��� ���� Ÿ����
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
	// x86 ��Ű��ó�� �븮�� �� ���̱� ������ �̷���. -> ������ �ּҰ� 4����Ʈ�̱⿡ �迭�� �����ּҷ� ����
	__asm
	{
		jmp	pShell
	}
}