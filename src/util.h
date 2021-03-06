/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include "core.h"
#include <cpputil/printing.hpp>

String get_wsa_error_string();
ulong get_millisec();
Vector<String> get_filenames_in_dir(String_ref dirname);
int parse_int(String_ref string);
bool dir_exists(String_ref dir);
bool file_exists(String_ref path);
char last_char_of(String_ref string);
bool str_contains(String_ref string, char character);
void print_error(String_ref message);
void wait_for_enter();
void replace_in_str(String_ref regex, String_ref replace, Mutable_string_ref string);

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

template <typename T>
bool vector_contains(Vector<T> vector, T element)
{
	for (T vec_element : vector)
	{
		if (vec_element == element)
			return true;
	}
	return false;
}
