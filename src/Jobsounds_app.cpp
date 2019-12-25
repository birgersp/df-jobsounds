/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Jobsounds_app.h"
#include "util.h"
#include <cpputil/string.hpp>
#include <cpputil/timing.hpp>
#include <time.h>
#include <cpputil/file.hpp>
#include "jobsounds.h"

const Vector<String> Jobsounds_app::default_script_locations = {
	"../hack/scripts",
	"hack/scripts"
};

void Jobsounds_app::run(const Vector<String>& arguments)
{
	sound_mixer.initialize();
	srand(time(nullptr));

	try
	{
		load_config();
	}
	catch (const cpputil::Exception& exception)
	{
		throw function_exception("Failed to load configuration: " + config_filename + ". " + exception.get_reason());
	}

	for (String_ref argument : arguments)
	{
		try
		{
			parse_argument(argument);
		}
		catch (const cpputil::Exception& exception)
		{
			throw function_exception("Invalid argument: " + argument + ". " + exception.get_reason());
		}
	}

	if (job_sounds.size() == 0)
	{
		print_line("Warning: no sounds loaded");
	}

	get_scripts_dir();
	script_path = dfhack_scripts_dir + "/jobsounds.lua";
	if (not file_exists(script_path))
	{
		print_line("Script not found, installing script.");
		install_script();
	}

	if (demo.enable)
	{
		run_demo();
	}
	else
	{
		run_server();
	}
}

void Jobsounds_app::load_config()
{
	Vector<String> lines = cpputil::read_file_lines(config_filename);
	uint line_index = 0;
	for (String_ref line : lines)
	{
		line_index++;
		if (line.size() > 0)
		{
			if (line[0] != '#')
				try
				{
					parse_argument(line);
				}
				catch (const cpputil::Exception& exception)
				{
					throw function_exception("Line " + to_string(line_index) + ". " + exception.get_reason());
				}
		}
	}
}

void Jobsounds_app::parse_argument(String_ref argument)
{
	Vector<String> equals_split = cpputil::split_string(argument, '=');
	if (equals_split.size() == 2)
	{
		String_ref key = equals_split[0];
		String_ref value = equals_split[1];
		if (key == "demo")
		{
			demo.enable = true;
			demo.job_id = parse_int(value);
		}
		else
		{
			throw function_exception("Unrecognized key: " + key);
		}
		return;
	}

	Vector<String> comma_split = cpputil::split_string(argument, ',');
	if (comma_split.size() == 3)
	{
		int job_id = parse_int(comma_split[0]);
		String dirname = comma_split[1];
		int min_time = parse_int(comma_split[2]);
		if (job_sounds.get(job_id) != nullptr)
		{
			print_line("Warning: sounds are already added for job " + to_string(job_id) + ". These sounds will be unloaded.");
		}
		print_line("Loading sounds for job: " + to_string(job_id));
		Vector<String> filenames = get_filenames_in_dir(dirname);
		Vector<Sound> sounds;
		for (String_ref filename : filenames)
		{
			print_line(" " + filename);
			Sound sound = sound_mixer.load_sound(filename);
			sounds.push_back(sound);
		}
		job_sounds.put(job_id, sounds);
		inteval_manager.set_sound_interval(job_id, min_time);
		return;
	}

	throw function_exception("Invalid syntax.");
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
	int unit_id = parse_int(split[0]);
	int job_id = parse_int(split[1]);
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
		uint random_index = rand() % sounds->size();
		const Sound& sound = (*sounds)[random_index];
		sound_mixer.play(sound);
		inteval_manager.set_event(unit_id, job_id, timestamp);
	}
}

void Jobsounds_app::run_demo()
{
	print_line("Running demo for job id: " + to_string(demo.job_id));
	while (true)
	{
		process_unit_job(0, demo.job_id);
		cpputil::sleep_mS(20);
	}
}

void Jobsounds_app::run_server()
{
	print_line("Starting server.");
	server.bind(port);
	while (true)
	{
		print_line("Waiting for a connection.");
		auto connection = server.accept_connection();
		print_line("Connection established.");
		process_connection(connection);
	}
}

void Jobsounds_app::install_script()
{
	std::ofstream file;
	file.open(script_path, std::ios::out);
	if (file.is_open() == false)
		throw function_exception("Failed to open file");
	file << JOBSOUNDS_SOURCE;
	file.close();
}

void Jobsounds_app::get_scripts_dir()
{
	print_line("Searching for scripts directory.");
	String dir_prefix = df_dir;
	if (last_char_of(dir_prefix) != '/')
		dir_prefix += '/';
	print_line("Scanning directories:");
	if (dfhack_scripts_dir == "")
	{
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
	}
	if (dfhack_scripts_dir == "")
	{
		throw function_exception("Script directory not found.");
	}
}
