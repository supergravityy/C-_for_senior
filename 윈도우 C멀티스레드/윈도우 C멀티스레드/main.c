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

	for (int i = 0; i < 20000; i++) // 200�������� ����Ǿ�, ��Ŀ�����尡 ����ȴ� -> ���ҽ� ����� �ʹ� ũ��
		nData++;

	// ��Ŀ �����尡 ����ɶ������� �ð��� �ʿ� -> ������join ���� �Լ�
	printf("g_nData : %d\n", g_nData);
	puts("mainTh_end\n");
	return 0;
}