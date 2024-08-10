#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<windows.h>
#include<process.h>
#include<stdio.h>
#include<string.h>

//#define BUG

char* g_Msg = 0; // 임계구간 변수

# ifdef BUG // 버그상황


void thread_set(void* paras) // 해당 변수을 갖고 동적할당
{
	while (1)
	{
		if (g_Msg == 0)
		{
			g_Msg = (char*)malloc(64);
			strcpy(g_Msg, "Hello\n");
		}
		//Sleep(1); // 이걸 안쓰면, 스레드가 리소스를 혼자 독차지 할 수도 있음 + 1ms 는 매우 긴 시간이다.

		/*
		* Sleep 함수를 사용해서 근사하게 나마 동기화를 맞춰, 임계지점에서의 크래쉬를 피할 수도 있다.
		* 해당 문제는 strcpy에서 문자열을 전역변수로 복사하려 하는데, 갑자기 context switching이 일어나 버리면서,
		* 할당해놓은 공간이 할당해제 되어버렸다 -> NULL에다가 문자열 복사는 잘못된 접근 -> OS의 철퇴
		* 
		* 그러나, sleep 함수를 사용함으로써 원래 논리적으로는 죽어야 하는코드가 살아있는 척을 해서 
		* 예상치 못한 순간에 죽어버려 디버깅을 하기 어렵게 만들 수도 있다. 
		* 조심해서 사용하여야 한다. -> sleep을 쓰면, 해당 스레드는 스레드 스케줄러에서 해당 시간동안 제외된다.
		*/
	}
}

void thread_reset(void* paras) // 해당 변수를 갖고 할당해제
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

# else // 동기화를 맞춰준 코드

CRITICAL_SECTION g_cs; // 교차로의 신호등 같은 객체

/*
* 그러나 critical_section과 mutex는 비슷하지만 다른데, 뮤텍스는 커널영역에서 작업이 이루어지는 반면
* critical_section은 유저영역에서 작업이 이루어진다
*/

void thread_set(void* paras) // 해당 변수을 갖고 동적할당
{
	while (1)
	{
		EnterCriticalSection(&g_cs);
		if (g_Msg == 0)
		{
			g_Msg = (char*)malloc(64);
			strcpy(g_Msg, "Hello\n");
		}
		//Sleep(1);		// 이제 슬립은 필요없다
		LeaveCriticalSection(&g_cs);
	}
}

void thread_reset(void* paras) // 해당 변수를 갖고 할당해제
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
	InitializeCriticalSection(&g_cs); // 뮤텍스같은 객체 초기화

	_beginthread(thread_set, 0, 0);
	_beginthread(thread_reset, 0, 0);


	while (_getch() != 'q')
	{
		EnterCriticalSection(&g_cs); // pthread_mutex_trylock 같은 함수
		if (g_Msg != 0)
			puts(g_Msg);
		else
			puts("Empty\n");
		LeaveCriticalSection(&g_cs); // pthread_mutex_unlock 같은 함수
	}

	DeleteCriticalSection(&g_cs); // 해당객체 삭제
	return 0;
}

#endif