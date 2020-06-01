/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Dwarf_job_msg.h"
#include "util.h"
#include <cpputil/string.hpp>

Dwarf_job_msg parse_dwarf_job_msg(String_ref string)
{
	Vector<String> split = split_string(string, ' ');
	Dwarf_job_msg message = {
		.dwarf_id = parse_int(split[0]),
		.job_id = parse_int(split[1])
	};
	return message;
}
