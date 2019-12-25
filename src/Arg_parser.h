/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <functional>
#include <cpputil/core.hpp>
#include <cpputil/Map.hpp>

typedef std::function<void() > Command_callback;
typedef std::function<void(String_ref) > Setting_callback;

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
	bool parse_as_command(String_ref string);
	bool parse_as_setting(String_ref string);

private:

	cpputil::Map<String, Command> commands;
	cpputil::Map<String, Setting> settings;

};

#endif /* ARG_PARSER_H */
