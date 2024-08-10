#include <stdio.h>

void main()
{
	char buffer1[1024] = "Hello Window!\n";
	printf("%s", buffer1);
	char buffer2[1024 * 1024] = "Hello Clang!\n";
	printf("%s", buffer2);
}