#ifndef CORE_H
#define CORE_H

#include <string>
#include <iostream>
#include <cpputil/core.hpp>
#include <cpputil/errorhandling.hpp>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OS_WINDOWS
#endif

#define print_line(value) std::cout << value << std::endl;

typedef const char *C_String;
typedef const std::string& String_Ref;
typedef std::string& Mutable_String_Ref;
typedef const cpputil::Exception& Exception;

#endif /* CORE_H */
