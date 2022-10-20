// Demo04Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo04Server.h"

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
	int nRetCode = 0;
    int err; 
    bool rc; 
    HANDLE hPipeHandle1; 
      
    char lpName[] = "\\\\.\\pipe\\myPipe"; 
    char InBuffer[50] = ""; 
    char OutBuffer[50] = ""; 
    DWORD BytesRead, BytesWrite; 
      
    //创建一个命名管道  
    hPipeHandle1 = CreateNamedPipe((LPCTSTR)lpName, 
		//访问模式，单or双
        PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED | WRITE_DAC , 
        PIPE_TYPE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 20, 30,  
        NMPWAIT_USE_DEFAULT_WAIT,
		(LPSECURITY_ATTRIBUTES)NULL); 
    //判断命名管道是否创建成功
  
    if((hPipeHandle1 == INVALID_HANDLE_VALUE) || (hPipeHandle1 == NULL)) 
    { 
        err = GetLastError(); 
        printf("Server Pipe Create Fail! err = %d\n", err); 
        exit(1);  
    } 
    else
        printf("Server Pipe Create Success!"); 
          
    while(TRUE) 
    { 
        //连接命名管道  
        rc = ConnectNamedPipe(hPipeHandle1, NULL); 
		//判断服务器连接命名管道是否成功
        if (rc == 0) 
        { 
            err = GetLastError(); 
            printf("Server Pipe Connect Fail! err = %d\n", err); 
            exit(2); 
        } 
        else
            printf("Server Pipe Connect Success!\n"); 
        strcpy(InBuffer, ""); 
		strcpy(OutBuffer, ""); 
        //向命名管道中读数据  
        rc = ReadFile(hPipeHandle1,InBuffer, sizeof(InBuffer), &BytesRead,  
        (LPOVERLAPPED)NULL); 
        if (rc == 0 && BytesRead == 0) 
        { 
            err = GetLastError(); 
            printf("Server Read Pipe Fail! err = %d\n", err); 
            exit(2); 
        } 
        else
            printf("Server Read Pipe Success!\nDATA from Client is = %s\n",  
            InBuffer); 
        rc = strcmp(InBuffer, "end"); 
        if (rc == 0) 
            break; 
        printf("Please Input Data to Send"); 
        scanf("%s", OutBuffer); 
        //向命名管道中写数据  
        rc = WriteFile(hPipeHandle1, OutBuffer, sizeof(OutBuffer), &BytesWrite,  
        (LPOVERLAPPED)NULL); 
        if (rc == 0) 
            puts("Server Write Pipe Fail!"); 
        else
            puts("Server Write Pipe Success!"); 
        //拆除与命名管道的连接  
        DisconnectNamedPipe(hPipeHandle1); 
        rc = strcmp(OutBuffer, "end"); 
        if (rc == 0) 
            break; 
    } 
    printf("Now Server be END!"); 
    CloseHandle(hPipeHandle1); 
    return nRetCode; 


}

