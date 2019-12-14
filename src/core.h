#ifndef CORE_H
#define CORE_H

#include <string>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OS_WINDOWS
#endif

typedef unsigned int uint;

typedef const char* C_String;
typedef const std::string& String_Ref;
typedef std::string& Mutable_String_Ref;

#endif /* CORE_H */
