HANDLE CreateThread(
	LPSECURITY_ATTRIBUTES lpThreadAttributes,    //为线程指定安全属性
	DWORD dwStackSize,  //线程堆栈的大小
	LPVOID lpparameter,  //函数中要传递的参数
	DWORD dwCreationFlags, //指定线程创建后所处的状态
	LPDWORD lpThread  //系统返回的线程标识符
);
