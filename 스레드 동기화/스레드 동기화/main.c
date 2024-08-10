#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<windows.h>
#include<process.h>
#include<stdio.h>
#include<string.h>

//#define BUG

char* g_Msg = 0; // �Ӱ豸�� ����

# ifdef BUG // ���׻�Ȳ


void thread_set(void* paras) // �ش� ������ ���� �����Ҵ�
{
	while (1)
	{
		if (g_Msg == 0)
		{
			g_Msg = (char*)malloc(64);
			strcpy(g_Msg, "Hello\n");
		}
		//Sleep(1); // �̰� �Ⱦ���, �����尡 ���ҽ��� ȥ�� ������ �� ���� ���� + 1ms �� �ſ� �� �ð��̴�.

		/*
		* Sleep �Լ��� ����ؼ� �ٻ��ϰ� ���� ����ȭ�� ����, �Ӱ����������� ũ������ ���� ���� �ִ�.
		* �ش� ������ strcpy���� ���ڿ��� ���������� �����Ϸ� �ϴµ�, ���ڱ� context switching�� �Ͼ �����鼭,
		* �Ҵ��س��� ������ �Ҵ����� �Ǿ���ȴ� -> NULL���ٰ� ���ڿ� ����� �߸��� ���� -> OS�� ö��
		* 
		* �׷���, sleep �Լ��� ��������ν� ���� �������δ� �׾�� �ϴ��ڵ尡 ����ִ� ô�� �ؼ� 
		* ����ġ ���� ������ �׾���� ������� �ϱ� ��ư� ���� ���� �ִ�. 
		* �����ؼ� ����Ͽ��� �Ѵ�. -> sleep�� ����, �ش� ������� ������ �����ٷ����� �ش� �ð����� ���ܵȴ�.
		*/
	}
}

void thread_reset(void* paras) // �ش� ������ ���� �Ҵ�����
{
	while (1)
	{
		if (g_Msg != 0)
		{
			free(g_Msg);
			g_Msg = NULL;
		}
		//Sleep(1);
	}
}

int main()
{
	_beginthread(thread_set, 0, 0);
	_beginthread(thread_reset, 0, 0);
	

	while (_getch() != 'q')
	{
		if (g_Msg != 0)
			puts(g_Msg);
		else
			puts("Empty\n");
	}

	//DeleteCriticalSection(&g_cs);
	return 0;
}

# else // ����ȭ�� ������ �ڵ�

CRITICAL_SECTION g_cs; // �������� ��ȣ�� ���� ��ü

/*
* �׷��� critical_section�� mutex�� ��������� �ٸ���, ���ؽ��� Ŀ�ο������� �۾��� �̷������ �ݸ�
* critical_section�� ������������ �۾��� �̷������
*/

void thread_set(void* paras) // �ش� ������ ���� �����Ҵ�
{
	while (1)
	{
		EnterCriticalSection(&g_cs);
		if (g_Msg == 0)
		{
			g_Msg = (char*)malloc(64);
			strcpy(g_Msg, "Hello\n");
		}
		//Sleep(1);		// ���� ������ �ʿ����
		LeaveCriticalSection(&g_cs);
	}
}

void thread_reset(void* paras) // �ش� ������ ���� �Ҵ�����
{
	while (1)
	{
		EnterCriticalSection(&g_cs);
		if (g_Msg != 0)
		{
			free(g_Msg); 
			g_Msg = NULL;
		}
		//Sleep(1);
		LeaveCriticalSection(&g_cs);
	}
}

int main()
{
	InitializeCriticalSection(&g_cs); // ���ؽ����� ��ü �ʱ�ȭ

	_beginthread(thread_set, 0, 0);
	_beginthread(thread_reset, 0, 0);


	while (_getch() != 'q')
	{
		EnterCriticalSection(&g_cs); // pthread_mutex_trylock ���� �Լ�
		if (g_Msg != 0)
			puts(g_Msg);
		else
			puts("Empty\n");
		LeaveCriticalSection(&g_cs); // pthread_mutex_unlock ���� �Լ�
	}

	DeleteCriticalSection(&g_cs); // �ش簴ü ����
	return 0;
}

#endif