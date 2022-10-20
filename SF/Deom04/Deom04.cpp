// Deom04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Deom04.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	bool rc = 0; 
      
    char lpName[] = "\\\\.\\pipe\\myPipe"; 
    char InBuffer[50] = ""; 
    char OutBuffer[50] = ""; 
    DWORD BytesRead; 
     int nRetCode = 0;     int err = 0; 
    while(1) 
    { 
        strcpy(InBuffer, "");
		strcpy(OutBuffer, ""); 
        printf("Input Data Please!"); 
        scanf("%s", InBuffer); 
        rc = strcmp(InBuffer, "end"); 
        if (rc == 0) 
        { 
            //连接命名管道  
            rc = CallNamedPipe(lpName, InBuffer, sizeof(InBuffer), OutBuffer,  
                sizeof(OutBuffer), &BytesRead, NMPWAIT_USE_DEFAULT_WAIT); 
            break; 
        } 
        //等待命名管道  
        rc = WaitNamedPipe(lpName, NMPWAIT_WAIT_FOREVER); 
        if (rc == 0) 
        { 
            err = GetLastError(); 
            printf("Wait Pipe Fail! err = %d\n", err); 
            exit(1); 
        } 
        else
            printf("Wait Pipe Success!\n"); 
        rc = CallNamedPipe(lpName, InBuffer, sizeof(InBuffer), OutBuffer,  
            sizeof(OutBuffer), &BytesRead, NMPWAIT_USE_DEFAULT_WAIT); 
        rc = strcmp(OutBuffer, "end");   
        if (rc == 0) 
            break; 
        if (rc == 0) 
        { 
            err = GetLastError(); 
            printf("Pipe Call Fail! err = %d\n", err); 
            exit(1); 
        } 
        else
            printf("Pipe Call Success!\nData from Server is %s\n", OutBuffer); 
    } 
    puts("Now Client to be End!"); 
    return nRetCode; 
}



