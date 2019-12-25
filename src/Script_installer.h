/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SCRIPT_INSTALLER_H
#define SCRIPT_INSTALLER_H

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

#endif /* SCRIPT_INSTALLER_H */
