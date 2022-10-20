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

static int count=5;//�ٽ���Դ
static HANDLE h1;
static HANDLE h2;
LPCRITICAL_SECTION hCriticalSection;   //����ָ���ٽ�������ĵ�ַָ��
CRITICAL_SECTION Critical;        //�����ٽ���

void func2(){
	int r2;

	EnterCriticalSection(hCriticalSection);    //�Ƿ���Ȩ�����ٽ���
	r2=count;
	_sleep(100);
	r2=r2+1;
	count=r2;
	printf("count in func2=%d\n",count);

	LeaveCriticalSection(hCriticalSection);     //�˳��ٽ���
}

void func1(){
	int r1;

	 EnterCriticalSection(hCriticalSection);    //�����ٽ���
	r1=count;
	_sleep(100);
	r1=r1+1;
	count=r1;
	printf("count in func1=%d\n",count);

	LeaveCriticalSection(hCriticalSection);     //�˳��ٽ���
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	DWORD dwThreadID1,dwThreadID2;

	hCriticalSection=&Critical;      //��ָ���ٽ��������ָ��ָ���ٽ���
	InitializeCriticalSection(hCriticalSection);  //��ʼ���ٽ���

	h1=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)func1,
		(LPVOID)NULL,
		0,&dwThreadID1);    //�����߳�func1

	if(h1==NULL) printf("Thread1 create FAIL!\n");
	else printf("Thread1 create Success!\n");
	h2=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)func2,
		(LPVOID)NULL,
		0,&dwThreadID2);    //�����߳�func2

	if(h2==NULL) printf("Thread2 create FAIL!\n");
	else printf("Thread2 create Success!\n");

	Sleep(1000);
	CloseHandle(h1);
    CloseHandle(h2);
	DeleteCriticalSection(hCriticalSection);  //ɾ���ٽ���
	ExitThread(0);//�˳�״̬��

	return nRetCode;
}



