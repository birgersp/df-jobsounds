/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Dwarf_job_msg.h"
#include <cpputil/Stringreader.hpp>
#include <cpputil/string.hpp>

Dwarf_job_msg parse_dwarf_job_msg(String_ref string)
{
	Vector<String> split = cpputil::split_string(string, ' ');
	Dwarf_job_msg message;
	message.dwarf_id = std::stoi(split[0]);
	message.job_id = std::stoi(split[1]);
	return message;
}
