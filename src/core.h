#ifndef CORE_H
#define CORE_H

#include <string>
#include <iostream>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OS_WINDOWS
#endif

#define print_line(value) std::cout << value << std::endl;

typedef unsigned int uint;

typedef const char *C_String;
typedef const std::string &String_Ref;
typedef std::string &Mutable_String_Ref;

#endif /* CORE_H */
