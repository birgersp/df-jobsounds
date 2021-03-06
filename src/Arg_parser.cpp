/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/string.hpp>
#include <cpputil/errorhandling.hpp>

#include "Arg_parser.h"
#include "core.h"

void Arg_parser::add_command(String command, Command_callback callback, String description)
{
	Command command_obj = {
		.callback = callback,
		.description = description
	};
	commands.put(command, command_obj);
}

void Arg_parser::add_setting(String keyword, Setting_callback callback, String description)
{
	Setting setting_obj;
	setting_obj.callback = callback;
	setting_obj.description = description;
	settings.put(keyword, setting_obj);
}

void Arg_parser::parse_as_command(String_ref string)
{
	Command* command = commands.get(string);
	if (command != nullptr)
	{
		command->callback();
	}
	else
	{
		throw function_exception("Unrecognized command: " + string);
	}
}

void Arg_parser::parse_as_setting(String_ref string)
{
	Vector<String> equals_split = split_string(string, '=');
	if (equals_split.size() != 2)
		throw function_exception("Invalid syntax. Expected (key)=(value)");

	Setting* setting = settings.get(equals_split[0]);
	if (setting == nullptr)
		throw function_exception("Unrecognized setting: " + equals_split[0]);

	setting->callback(equals_split[1]);
}
