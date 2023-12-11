//
// repo:			socket_leak_investigator
// file:            main_socket_keak_analyze_test01.cpp
// path:			src/tests/main_socket_keak_analyze_test01.cpp
// created on:		2023 Dec 07
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <sock_leak_invest/export_symbols.h>
#include <stdio.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
typedef SOCKET  socket_t;
#define SleepMsIntr(_x)     SleepEx(_x,TRUE)
#define getpid              GetCurrentProcessId
#endif
#include <cinternal/undisable_compiler_warnings.h>


int main(int a_argc, char* a_argv[])
{
	socket_t aSocket;
	(void)a_argc;
	(void)a_argv;

    int pid = (int)getpid();

	while (1) {
		aSocket = socket(AF_INET, SOCK_STREAM, 0);
		fprintf(stdout, "pid: %d, aSocket = %d\n", pid, (int)aSocket);
        SleepMsIntr(2000);
	}

	return 0;
}





static void main_socket_leak_analyze_test01_c_clean(void) CPPUTILS_NOEXCEPT {
#ifdef _WIN32
    WSACleanup();
#endif
}


CPPUTILS_CODE_INITIALIZER(main_socket_leak_analyze_test01_c_init) {
#ifdef _WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    //SOCKET aTestSocket;

    wVersionRequested = MAKEWORD(2, 2);

    if (WSAStartup(wVersionRequested, &wsaData) != 0) {
        exit(1);
    }

    /* Confirm that the WinSock DLL supports 2.2.		*/
    /* Note that if the DLL supports versions greater	*/
    /* than 2.2 in addition to 2.2, it will still return*/
    /* 2.2 in wVersion since that is the version we		*/
    /* requested.										*/

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        WSACleanup();
        exit(1);
    }

    atexit(&main_socket_leak_analyze_test01_c_clean);
#endif
}
