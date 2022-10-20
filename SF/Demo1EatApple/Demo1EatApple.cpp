// Demo1EatApple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo1EatApple.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

void eatApple(int apple_number){
	Sleep((3 - apple_number) * 1000);
	printf("I'm eating apple #%d.\n", apple_number);
	while(1) {
		printf("#%d id is exiting.\n\n",apple_number);
		ExitThread(0);
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	HANDLE handle1 = NULL;
	HANDLE handle2 = NULL;
	HANDLE handle3 = NULL;
	DWORD ThreadID1 = NULL;
	DWORD ThreadID2 = NULL;
	DWORD ThreadID3 = NULL;
	int a=0;
	int b=1;
	int c=2;

	handle1=CreateThread((LPSECURITY_ATTRIBUTES) NULL,
		0,
		(LPTHREAD_START_ROUTINE) eatApple,
		(LPVOID)a,
		0,
		&ThreadID1);

	handle2=CreateThread((LPSECURITY_ATTRIBUTES) NULL,
		0,
		(LPTHREAD_START_ROUTINE) eatApple,
		(LPVOID)b,
		0,
		&ThreadID2);

	handle3=CreateThread((LPSECURITY_ATTRIBUTES) NULL,
		0,
		(LPTHREAD_START_ROUTINE) eatApple,
		(LPVOID)c,
		0,
		&ThreadID3);

	Sleep(10000);
	return nRetCode;
}


