/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Jobsounds_app.h"
#include "core.h"
#include <cpputil/Stringreader.hpp>

void Jobsounds_app::run(const Vector<String>& arguments)
{
	for (String_ref argument : arguments)
		parse_argument(argument);
	server.bind(port);
	while (true)
	{
		auto connection = server.accept_connection();
		process_connection(connection);
	}
}

void Jobsounds_app::parse_argument(String_ref argument)
{
	// todo: parse arguments
}

void Jobsounds_app::process_connection(Socket_Connection& connection)
{
	String message;
	while (not connection.is_closed())
	{
		message.clear();
		connection.readline(message);
		parse_message(message);
	}
}

void Jobsounds_app::parse_message(String_ref message)
{

}
