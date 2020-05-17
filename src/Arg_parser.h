/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include <functional>
#include <cpputil/core.hpp>
#include <cpputil/Map.hpp>

using Command_callback = std::function<void() >;
using Setting_callback = std::function<void(String_ref) >;

class Arg_parser
{
public:

	struct Command
	{
		Command_callback callback;
		String description;
	};

	struct Setting
	{
		Setting_callback callback;
		String description;
	};

	void add_command(String command, Command_callback callback, String description = "");
	void add_setting(String keyword, Setting_callback callback, String description = "");
	void parse_as_command(String_ref string);
	void parse_as_setting(String_ref string);

	Map<String, Command> commands;
	Map<String, Setting> settings;

};
