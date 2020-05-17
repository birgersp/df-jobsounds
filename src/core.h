/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef CORE_H
#define CORE_H

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

#endif /* CORE_H */
