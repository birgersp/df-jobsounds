/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/testing.hpp>

#include "cpputil/Stringreader.hpp"
#include "Dwarf_job_msg.h"

void test_parse()
{
	register_test();
	Dwarf_job_msg message = parse_dwarf_job_msg("123 456");
	assert_equals(123, message.dwarf_id);
	assert_equals(456, message.job_id);
}

bool test_dwarf_job_msg()
{
	return test_all
			({
			test_parse,
	});
}
