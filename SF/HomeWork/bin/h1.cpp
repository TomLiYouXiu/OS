//#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include "01.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void ThreadName1();
static HANDLE hHandle1=NULL;
DWORD dwThreadID1;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	hHandle1 = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
		0,
		(LPTHREAD_START_ROUTINE) ThreadName1,
		(LPVOID) NULL,
		0, &dwThreadID1 );
	Sleep(5000);
	CloseHandle(hHandle1);
	ExitThread(0);

	return nRetCode;
}

void ThreadName1()
{
	printf("Thread is running!");
}

