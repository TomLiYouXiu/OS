// Demo01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo01.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
//线程对应打印函数
void ThreadName()
{
	printf("Thread is Running!\n");
}
static HANDLE hHandle1=NULL; 
DWORD ThreadID1;
  
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	HANDLE hHandle = NULL;
	DWORD ThreadID = NULL;
    
	hHandle=CreateThread((LPSECURITY_ATTRIBUTES) NULL,
		0,
		(LPTHREAD_START_ROUTINE) ThreadName,
		//创建线程
		(LPVOID)NULL,
		0,
		&ThreadID);
	Sleep(5000); //挂起5s
	CloseHandle(hHandle);//关闭句柄
	ExitThread(0);//撤销线程
	
	return nRetCode;

}

