/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/string.hpp>

#include "Arg_parser.h"

void Arg_parser::add_command(String command, Command_callback callback, String description)
{
	Command command_obj;
	command_obj.callback = callback;
	command_obj.description = description;
	commands.put(command, command_obj);
}

void Arg_parser::add_setting(String keyword, Setting_callback callback, String description)
{
	Setting setting_obj;
	setting_obj.callback = callback;
	setting_obj.description = description;
	settings.put(keyword, setting_obj);
}

bool Arg_parser::parse_as_command(String_ref string)
{
	Command* command = commands.get(string);
	if (command != nullptr)
	{
		command->callback();
		return true;
	}
	return false;
}

bool Arg_parser::parse_as_setting(String_ref string)
{
	Vector<String> equals_split = cpputil::split_string(string, '=');
	if (equals_split.size() == 2)
	{
		Setting* setting = settings.get(equals_split[0]);
		if (setting != nullptr)
		{
			setting->callback(equals_split[1]);
			return true;
		}
	}
	return false;
}
