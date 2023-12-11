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
#endif
#include <cinternal/undisable_compiler_warnings.h>


int main(int a_argc, char* a_argv[])
{
	socket_t aSocket;
	(void)a_argc;
	(void)a_argv;

	while (1) {
		aSocket = socket(AF_INET, SOCK_STREAM, 0);
		fprintf(stdout, "aSocket = %d\n", (int)aSocket);
	}

	return 0;
}


//#pragma pack(1)
//struct patch_t
//{
//	BYTE nPatchType; //OP code, 0xE9 for JMP
//	DWORD dwAddress;
//};
//#pragma pack()
//
//
//BOOL apply_patch(BYTE eType, DWORD dwAddress, const void* pTarget, DWORD* a_orig_size, BYTE* replaced)
//{
//	SIZE_T orig_size;
//	DWORD dwOldValue, dwTemp;
//	struct patch_t pWrite =
//	{
//		eType,
//		(DWORD)pTarget - (dwAddress + sizeof(DWORD) + sizeof(BYTE))
//	};
//	VirtualProtect((LPVOID)dwAddress, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOldValue);
//	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwAddress, (LPVOID)replaced, sizeof(pWrite), &orig_size); //Keep track of the bytes we replaced
//	BOOL bSuccess = WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddress, &pWrite, sizeof(pWrite), NULL);
//	VirtualProtect((LPVOID)dwAddress, sizeof(DWORD), dwOldValue, &dwTemp);
//
//	*a_orig_size = orig_size;
//
//	return bSuccess;
//}
//
//
//static DWORD addr_socket = 0;
//static DWORD addr_closesocket = 0;
//static DWORD orig_size_socket = 0;
//static DWORD orig_size_closesocket = 0;
//static BYTE replaced_socket[10];
//static BYTE replaced_closesocket[10];
//typedef SOCKET(WSAAPI* TypeSocket)(int af, int type, int protocol);
//typedef int (*TypeClosesocket)(SOCKET s);
//static TypeSocket s_socket_original;
//static TypeClosesocket s_closesocket_original;
//static TypeSocket s_pSocket = NULL;
//static TypeClosesocket s_pClosesocket = NULL;
//
//static SOCKET WSAAPI SockLeakHookCrtSocketStatic(int a_af, int a_type, int a_protocol) CPPUTILS_NOEXCEPT
//{
//	return (*s_socket_original)(a_af, a_type, a_protocol);
//}
//
//
//static int SockLeakHookRemSocketStatic(SOCKET a_sock) CPPUTILS_NOEXCEPT
//{
//	return (*s_closesocket_original)(a_sock);
//}
//
//
//static DWORD WINAPI initialize(void)
//{
//	DWORD addr;
//	BYTE replaced[10];
//	DWORD orig_size;
//
//
//	addr_socket = (DWORD)GetProcAddress(GetModuleHandle(TEXT("WS2_32.dll")), "socket");
//	addr_closesocket = (DWORD)GetProcAddress(GetModuleHandle(TEXT("WS2_32.dll")), "closesocket");
//
//	s_socket_original = (TypeSocket)GetProcAddress(GetModuleHandle(TEXT("WS2_32.dll")), "socket");
//	s_closesocket_original = (TypeClosesocket)GetProcAddress(GetModuleHandle(TEXT("WS2_32.dll")), "closesocket");
//
//	//TODO: Clean this area up and move these to some inline function
//	addr = addr_socket;
//	if (apply_patch(0xE9, addr, (void*)(&SockLeakHookCrtSocketStatic), &orig_size_socket, replaced_socket)) //Note we only store this replaced because this is the original winsock function code, which we need to put back upon closing
//	{
//		s_pSocket = (TypeSocket)VirtualAlloc(NULL, orig_size_socket << 2, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
//		memcpy((void*)s_pSocket, replaced_socket, orig_size_socket);
//		apply_patch(0xE9, (DWORD)s_pSocket + orig_size_socket, (void*)(addr + orig_size_socket), &orig_size, replaced);
//	}
//
//	addr = addr_closesocket;
//	if (apply_patch(0xE9, addr, (void*)(&SockLeakHookRemSocketStatic), &orig_size_closesocket, replaced_closesocket))
//	{
//		s_pClosesocket = (TypeClosesocket)VirtualAlloc(NULL, orig_size_closesocket << 2, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
//		memcpy((void*)s_pClosesocket, replaced_closesocket, orig_size_closesocket);
//		apply_patch(0xE9, (DWORD)s_pClosesocket + orig_size_closesocket, (void*)(addr + orig_size_closesocket), &orig_size, replaced);
//	}
//
//	//Initialize lists
//	//INIT_LIST_HEAD(&ws_handlers.ws_handlers_send);
//	//INIT_LIST_HEAD(&ws_handlers.ws_handlers_recv);
//	//INIT_LIST_HEAD(&ws_plugins.plugins);
//	//load_plugins("./plugins/", &ws_plugins);
//	return 0;
//}
