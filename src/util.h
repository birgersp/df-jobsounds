/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef UTIL_H
#define UTIL_H

#include "core.h"
#include <cpputil/printing.hpp>

String get_wsa_error_string();
ulong get_millisec();

template <typename T>
void print_line(T data)
{
	cpputil::print_line(data);
}

#endif
