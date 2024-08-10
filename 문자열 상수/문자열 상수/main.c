#include <stdio.h>

int main()
{
	char* str = "Hello World\n"; // 여기서 이 문자열을 디버깅 모드에서 메모리창으로 변경시,
	printf(str);
	printf("Hello World\n"); // 이 상수처럼 보이는 문자열도 덩달이 변경된다 왜그러지?
	
	return 0;
}