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
Vector<String> get_filenames_in_dir(String_ref dirname);

template <typename T>
void print_line(T data)
{
	cpputil::print_line(data);
}

template <typename T>
void print_vector(Vector<T> vector)
{
	for (T element : vector)
	{
		print_line(element);
	}
}

template <typename T>
String to_string(T data)
{
	return std::to_string(data);
}

#endif
