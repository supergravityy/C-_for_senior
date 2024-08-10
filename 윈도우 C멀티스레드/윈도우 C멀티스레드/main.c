#include <windows.h>
#include <process.h>
#include <stdio.h>

int g_nData;

void workerTh_func(void* paras)
{
	g_nData = 0;
	puts("workerTh_start\n");

	for (int i = 0; i < 200; i++)
		g_nData++;

	puts("workerTh_end\n");
	return;
}

int main()
{
	puts("mainTh_start\n");
	int nData = 0;
	
	_beginthread(workerTh_func, 0, 0);

	for (int i = 0; i < 20000; i++) // 200만번정도 실행되야, 워커스레드가 종료된다 -> 리소스 비용이 너무 크다
		nData++;

	// 워커 스레드가 수행될때까지의 시간이 필요 -> 스레드join 같은 함수
	printf("g_nData : %d\n", g_nData);
	puts("mainTh_end\n");
	return 0;
}