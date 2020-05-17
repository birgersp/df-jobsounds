/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include "core.h"

struct Dwarf_job_msg
{
	int dwarf_id;
	int job_id;
};

Dwarf_job_msg parse_dwarf_job_msg(String_ref string);
