//
// repo:			socket_leak_investigator
// file:			export_symbols.h
// path:			include/sock_leak_inves/export_symbols.h
// created on:		2023 Dec 07
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef SOCKET_LEAK_INVESTIGATOR_INCLUDE_SOCK_LEAK_INVEST_EXPORT_SYMBOLS_H
#define SOCKET_LEAK_INVESTIGATOR_INCLUDE_SOCK_LEAK_INVEST_EXPORT_SYMBOLS_H

#include <cinternal/internal_header.h>


#ifndef SOCKLKINV_EXPORT
#if defined(SOCKLKINV_COMPILING_SHARED_LIB)
#define SOCKLKINV_EXPORT CPPUTILS_DLL_PUBLIC
#elif defined(SOCKLKINV_USING_STATIC_LIB_OR_OBJECTS)
#define SOCKLKINV_EXPORT
#elif defined(SOCKLKINV_LOAD_FROM_DLL)
#define SOCKLKINV_EXPORT CPPUTILS_IMPORT_FROM_DLL
#else
#define SOCKLKINV_EXPORT CPPUTILS_DLL_PRIVATE
#endif
#endif


#endif  // #ifndef SOCKET_LEAK_INVESTIGATOR_INCLUDE_SOCK_LEAK_INVEST_EXPORT_SYMBOLS_H
