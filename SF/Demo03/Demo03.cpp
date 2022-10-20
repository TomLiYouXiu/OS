// Demo03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo03.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

static int count=5;//临界资源
static HANDLE h1;
static HANDLE h2;
LPCRITICAL_SECTION hCriticalSection;   //定义指向临界区对象的地址指针
CRITICAL_SECTION Critical;        //定义临界区

void func2(){
	int r2;

	EnterCriticalSection(hCriticalSection);    //是否有权进入临界区
	r2=count;
	_sleep(100);
	r2=r2+1;
	count=r2;
	printf("count in func2=%d\n",count);

	LeaveCriticalSection(hCriticalSection);     //退出临界区
}

void func1(){
	int r1;

	 EnterCriticalSection(hCriticalSection);    //进入临界区
	r1=count;
	_sleep(100);
	r1=r1+1;
	count=r1;
	printf("count in func1=%d\n",count);

	LeaveCriticalSection(hCriticalSection);     //退出临界区
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	DWORD dwThreadID1,dwThreadID2;

	hCriticalSection=&Critical;      //将指向临界区对象的指针指向临界区
	InitializeCriticalSection(hCriticalSection);  //初始化临界区

	h1=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)func1,
		(LPVOID)NULL,
		0,&dwThreadID1);    //创建线程func1

	if(h1==NULL) printf("Thread1 create FAIL!\n");
	else printf("Thread1 create Success!\n");
	h2=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)func2,
		(LPVOID)NULL,
		0,&dwThreadID2);    //创建线程func2

	if(h2==NULL) printf("Thread2 create FAIL!\n");
	else printf("Thread2 create Success!\n");

	Sleep(1000);
	CloseHandle(h1);
    CloseHandle(h2);
	DeleteCriticalSection(hCriticalSection);  //删除临界区
	ExitThread(0);//退出状态码

	return nRetCode;
}



