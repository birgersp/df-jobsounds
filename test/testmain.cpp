/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "core.h"
#include "dwarf_job_msg_test.h"
#include <cpputil/testing.hpp>

int main(int argc, char **argv)
{
	Vector<cpputil::Bool_function> test_functions = {
		test_dwarf_job_msg
	};
	if (cpputil::all_succeed(test_functions))
	{
		return 0;
	}
	return 1;
}
