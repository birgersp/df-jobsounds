#include "util.h"
#include <winsock2.h>
#include <sys/time.h>

std::string get_wsa_error_string()
{
	wchar_t *buffer = NULL;
	FormatMessageW(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				WSAGetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPWSTR) & buffer,
				0,
				NULL
				);
	std::wstring ws(buffer);
	std::string string(ws.begin(), ws.end());
	LocalFree(buffer);
	return string;
}

ulong get_millisec()
{
	timeval timeValue;
	gettimeofday(&timeValue, 0);
	ulong millisecs_1 = timeValue.tv_sec * 1000;
	ulong rest = timeValue.tv_usec / 1000;
	return millisecs_1 + rest;
}
