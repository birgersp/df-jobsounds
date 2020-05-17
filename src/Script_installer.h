/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include "core.h"

class Script_installer
{
public:

	String df_dir = ".";
	static const Vector<String> default_script_locations;
	bool check_script_exists();
	void install_script();

private:

	String dfhack_scripts_dir;
	String script_path;
	void find_script_path();

};
