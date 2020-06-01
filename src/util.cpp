/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "util.h"
#include <winsock2.h>
#include <sys/time.h>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

String get_wsa_error_string()
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
	String string(ws.begin(), ws.end());
	LocalFree(buffer);
	return string;
}

ulong get_millisec()
{
	timeval time_value;
	gettimeofday(&time_value, 0);
	ulong millisecs_1 = time_value.tv_sec * 1000;
	ulong rest = time_value.tv_usec / 1000;
	return millisecs_1 + rest;
}

Vector<String> get_filenames_in_dir(String_ref dirname)
{
	Vector<String> result;
	try
	{
		auto iterator = fs::directory_iterator(dirname);
		for (auto entry : iterator)
		{
			result.push_back(entry.path().string());
		}
	}
	catch (fs::__cxx11::filesystem_error error)
	{
		throw function_exception("Cannot list files in directory: " + dirname);
	}
	return result;
}

int parse_int(String_ref string)
{
	int result;
	try
	{
		result = std::stoi(string);
	}
	catch (std::invalid_argument error)
	{
		throw function_exception("Cannot parse to integer: " + string);
	}
	return result;
}

bool dir_exists(String_ref dir)
{
	auto status = fs::status(dir);
	return fs::is_directory(status);
}

bool file_exists(String_ref path)
{
	auto status = fs::status(path);
	return fs::is_regular_file(status);
}

char last_char_of(String_ref string)
{
	if (string.size() == 0)
		throw function_exception("String is empty");
	return (string[string.size() - 1]);
}

bool str_contains(String_ref string, char character)
{
	return string.find(character) != -1;
}

void print_error(String_ref message)
{
	print_error_string(message);
}

void wait_for_enter()
{
	system("pause");
}

void replace_in_str(String_ref regex, String_ref replace, Mutable_string_ref string)
{
	string = std::regex_replace(string, std::regex(regex), replace);
}
