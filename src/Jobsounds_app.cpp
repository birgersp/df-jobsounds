/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Jobsounds_app.h"
#include "util.h"
#include <cpputil/string.hpp>

void Jobsounds_app::run(const Vector<String>& arguments)
{
	sound_mixer.initialize();

	// TODO: load config file
	for (String_ref argument : arguments)
		parse_argument(argument);

	return;

	server.bind(port);
	while (true)
	{
		auto connection = server.accept_connection();
		process_connection(connection);
	}
}

void Jobsounds_app::parse_argument(String_ref argument)
{


	Vector<String> split = cpputil::split_string(argument, ',');
	int job_id = std::stoi(split[0]);
	String dirname = split[1];
	int min_time = std::stoi(split[2]);
	Vector<String> filenames = get_filenames_in_dir(dirname);
	Vector<Sound> sounds;
	for (String_ref filename : filenames)
	{
		Sound sound = sound_mixer.load_sound(filename);
		sounds.push_back(sound);
	}
	job_sounds.put(job_id, sounds);
	inteval_manager.set_sound_interval(job_id, min_time);
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
	process_unit_job(unit_id, job_id);
}

void Jobsounds_app::process_unit_job(int unit_id, int job_id)
{
	Vector<Sound>* sounds = job_sounds.get(job_id);
	if (sounds == nullptr)
		return;
	ulong timestamp = get_millisec();
	bool should_play = inteval_manager.sound_should_play(unit_id, job_id, timestamp);
	if (should_play)
	{
		// TODO: get random sound in vector
		const Sound& sound = (*sounds)[0];
		sound_mixer.play(sound);
		inteval_manager.set_event(unit_id, job_id, timestamp);
	}
}
