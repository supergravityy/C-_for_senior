#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define QUEUE_SIZE 100

char g_eventQueue[QUEUE_SIZE];	// 메인 스레드가 pop해서 실행할 이벤트가 저장됨
int g_counterHead = 0;			// 큐의 시작
int g_counterTail = 0;			// 큐의 끝

void add_event_copyStart()
{
	g_eventQueue[g_counterTail++] = 'x';
}

void add_event_copyEnd()
{
	g_eventQueue[g_counterTail++] = 'y';
}

void thread_userEvent(void* paras)
{
	char event;
	puts("user input thread - begin\n");

	while (event = _getch())
	{
		printf("user input event : %c\n", event);
		g_eventQueue[g_counterTail++] = event;
	}

	puts("user input thread - end\n");
}

void thread_copyFile(void* paras)
{
	add_event_copyStart();
	Sleep(3000); // 3초 휴식
	add_event_copyEnd();
}

void event_handlerA()
{
	puts("Event A : complete\n");
}

void event_handlerB()
{
	puts("Event B : complete\n");
}

void event_handlerC()
{
	puts("Event C : complete\n");
	_beginthread(thread_copyFile, 0, 0);
}

char dispatch_Event()
{
	char event = g_eventQueue[g_counterHead]; // 큐에서 하나를 pop 해서 머리가 다음 인덱스로

	if (event != 0)
		g_counterHead++;

	return event;
}

void main()
{
	char input = 0;
	_beginthread(thread_userEvent, 0, 0);

	while ((input = dispatch_Event()) != 'q')
	{
		switch (input) // 해당 이벤트에 맞는 핸들러를 실행시킨다.
		{
		case 'x':
			puts("File copyThread - start\n");
			break;
		case 'y':
			puts("File copyThread - end\n");
			break;
		case 'a':
			event_handlerA();
			break;
		case 'b':
			event_handlerB();
			break;
		case 'c':
			event_handlerC();
			break;
		default:
			break;
		}
		Sleep(1);
	}
	return;
}