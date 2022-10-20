// Demo02One.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo02One.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

static HANDLE hHandle1=NULL;

void chef(){
	printf("油条开始制作，预计等待时间5秒。\n");
	Sleep(5000);
	printf("油条制作完成!\n");

	BOOL rc;
	DWORD err;

	rc=ReleaseSemaphore(hHandle1,1,NULL);   //释放一个信号量
	err=GetLastError();                    //回调函数，上条语句是否完成
	printf("ReleaseSemaphore err=%d\n",err);
	if(rc==0){
		printf("Semaphore Release Fail!\n");
	}
	else{
		printf("Semaphore Release Success!rc=%d\n",rc);
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	DWORD dRes,err;
	
	hHandle1=CreateSemaphore(NULL,0,1,"SemaphoreName1");//创建一个信号量
	//判断是否创建成功
	if(hHandle1==NULL){
		printf("Semaphore Create Fail!\n");  
	}
	else{
		printf("Semaphore Create Success!\n");
	}

	hHandle1=OpenSemaphore(SYNCHRONIZE|SEMAPHORE_MODIFY_STATE,
		NULL,
		"SemaphoreName1");                              //打开一个信号量
	if(hHandle1==NULL){
		printf("Semaphore Open Fail!\n");
	}
	else{
		printf("Semaphore Open Success!\n");
	}
	
	HANDLE handle1=NULL;
	DWORD ThreadID1=NULL;
	//子线程
	handle1=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)chef,
		(LPVOID)NULL,
		0,
		&ThreadID1);

	dRes=WaitForSingleObject(hHandle1,INFINITE);

	err=GetLastError();
	if(err==0){
		printf("油条上菜完毕，请开动吧.\n");
	}
	//排错
	else{
		printf("WaitForSingleObject err=%d\n",err);
		if(dRes==WAIT_TIMEOUT) printf("TIMEOUT!dRes=%d\n",dRes);
		else if(dRes==WAIT_OBJECT_0)  printf("WAIT_OBJECT!dRes=%d\n",dRes);
		else if(dRes==WAIT_ABANDONED)  printf("WAIT_ABANDONED!Dres=%d\n",dRes);
		else printf("dRes=%d\n",dRes);
	}
	return nRetCode;
}

