/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "core.h"
#include "dwarf_job_msg_test.h"
#include "sound_interval_manager_test.h"
#include <cpputil/testing.hpp>

int main(int argc, char **argv)
{
	using namespace test;
	Vector<cpputil::Bool_function> test_functions = {
		test_dwarf_job_msg,
		sound_interval_manager::testsSucceed
	};
	if (cpputil::all_succeed(test_functions))
	{
		return 0;
	}
	return 1;
}
