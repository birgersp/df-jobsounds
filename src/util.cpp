#include "util.h"
#include <winsock2.h>

std::string get_wsa_error_string()
{
	wchar_t *buffer = NULL;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				   NULL, WSAGetLastError(),
				   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				   (LPWSTR)&buffer, 0, NULL);
	std::wstring ws(buffer);
	std::string string(ws.begin(), ws.end());
	LocalFree(buffer);
	return string;
}
