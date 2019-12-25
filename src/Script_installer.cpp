/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Script_installer.h"
#include "util.h"
#include "jobsounds_lua_transpiled.h"
#include <cpputil/errorhandling.hpp>
#include <cpputil/file.hpp>

const Vector<String> Script_installer::default_script_locations = {
	"hack/scripts",
	"../hack/scripts"
};

bool Script_installer::check_script_exists()
{
	if (dfhack_scripts_dir == "")
		find_script_path();
	return file_exists(script_path);
}

void Script_installer::install_script()
{
	if (dfhack_scripts_dir == "")
		find_script_path();
	print_line("Installing jobsounds script to: " + script_path);
	cpputil::write_file(script_path, JOBSOUNDS_LUA_TRANSPILED);
}

void Script_installer::find_script_path()
{
	print_line("Searching for scripts directory.");
	String dir_prefix = df_dir;
	if (last_char_of(dir_prefix) != '/')
		dir_prefix += '/';
	print_line("Scanning directories:");
	for (String dir : default_script_locations)
	{
		String possible_dir = dir_prefix + dir;
		print_line(" " + possible_dir);
		if (dir_exists(possible_dir))
		{
			dfhack_scripts_dir = possible_dir;
			break;
		}
	}
	if (dfhack_scripts_dir == "")
	{
		throw function_exception("Script directory not found.");
	}
	script_path = dfhack_scripts_dir + "/jobsounds.lua";
}
