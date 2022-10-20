// Demo02Many.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo02Many.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
void chef(int meal_code){

	if(meal_code==0){
	Sleep(5000);
	printf("油条制作完成!\n");
	}

	else if(meal_code==1){
	Sleep(3000);
	printf("豆浆制作完成!\n");
	}

	else if(meal_code==2){
	Sleep(9000);
	printf("茶叶蛋制作完成!\n");
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	DWORD dRes,err;
	
	HANDLE handle1=NULL;
	HANDLE handle2=NULL;
	HANDLE handle3=NULL;
	
	DWORD ThreadID1=NULL;
	DWORD ThreadID2=NULL;
	DWORD ThreadID3=NULL;

	int a=0;
	int b=1;
	int c=2;

	handle1=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)chef,
		(LPVOID)a,
		0,
		&ThreadID1);

	handle2=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)chef,
		(LPVOID)b,
		0,
		&ThreadID2);
	
	handle3=CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)chef,
		(LPVOID)c,
		0,
		&ThreadID3);
	
	HANDLE hHandles[3];
	hHandles[0]=handle1;
	hHandles[1]=handle2;
	hHandles[2]=handle3;
	dRes=WaitForMultipleObjects(3,hHandles,1,INFINITE);

	err=GetLastError();
	if(err==0){
		printf("所有菜品上菜完毕，请开动吧.\n");
	}
	else{
		printf("WaitForMultipleObjects err=%d\n",err);

		if(dRes==WAIT_TIMEOUT) printf("TIMEOUT!dRes=%d\n",dRes);
		else if(dRes==WAIT_OBJECT_0)  printf("WAIT_OBJECT!dRes=%d\n",dRes);
		else if(dRes==WAIT_ABANDONED)  printf("WAIT_ABANDONED!Dres=%d\n",dRes);
		else printf("dRes=%d\n",dRes);
	}

	return nRetCode;
}

