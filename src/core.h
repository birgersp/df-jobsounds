/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cpputil/core.hpp>
#include <cpputil/errorhandling.hpp>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OS_WINDOWS
#endif

template<class T>
using Vector = std::vector<T>;
