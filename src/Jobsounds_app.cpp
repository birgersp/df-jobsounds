/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Jobsounds_app.h"
#include "util.h"
#include <cpputil/string.hpp>

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
	Vector<String> split = cpputil::split_string(message, ' ');
	int unit_id = std::stoi(split[0]);
	int job_id = std::stoi(split[1]);
	Sound* sound = job_sounds.get(job_id);
	if (sound == nullptr)
		return;
	ulong timestamp = get_millisec();
	bool should_play = inteval_manager.sound_should_play(unit_id, job_id, timestamp);
	if (should_play)
	{
		sound_mixer.play(*sound);
		inteval_manager.set_event(unit_id, job_id, timestamp);
	}
}
