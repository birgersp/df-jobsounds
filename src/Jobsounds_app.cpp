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
#include "jobsounds_lua_transpiled.h"

Jobsounds_app::Jobsounds_app()
{
	arg_parser.add_command("help", [this]()
	{
		print_help_text();
		throw function_exception("Aborted.");
	}, "View help text.");

	arg_parser.add_command("install-script", [this]()
	{
		script_installer.install_script();
	}, "Create jobsounds script in DFHack directory, overwrite it if it already exists. If the script does not exist, it will be created even if this command is not invoked.");

	arg_parser.add_command("print-jobs", [this]()
	{
		print_jobs = true;
	}, "Print the unit and job id when such data is received from Dwarf Fortress.");

	arg_parser.add_setting("demo", [this](String_ref string)
	{
		demo.enable = true;
		demo.job_id = parse_int(string);
	}, "Loop a job to test how the sounds loaded for that job sounds. Example: demo=68.");

	arg_parser.add_setting("dfdir", [this](String_ref string)
	{
		script_installer.df_dir = string;
	}, "Explicitly set the Dwarf Fortress directory. Use this if you did not install jobsounds in the Dwarf Fortress folder. Example: dfdir=\"C:\\Dwarf Fortress\\\".");
}

void Jobsounds_app::run(const Vector<String>& arguments)
{
	if (arguments.size() == 1)
	{
		if (arguments[0] == "help")
		{
			print_help_text();
			return;
		}
	}

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

	if (not script_installer.check_script_exists())
	{
		script_installer.install_script();
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
	if (str_contains(argument, ','))
	{
		Vector<String> comma_split = cpputil::split_string(argument, ',');
		if (comma_split.size() != 3)
		{
			throw function_exception("Invalid syntax.");
		}
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
	}
	else if (str_contains(argument, '='))
	{
		arg_parser.parse_as_setting(argument);
	}
	else
	{
		arg_parser.parse_as_command(argument);
	}
}

void Jobsounds_app::process_connection(Socket_Connection& connection)
{
	String message;
	while (not connection.is_closed())
	{
		message.clear();
		connection.readline(message);
		try
		{
			parse_message(message);
		}
		catch (Exception e)
		{
			throw function_exception("Failed to parse message: " + message + ". " + e.get_reason());
		}
	}
}

void Jobsounds_app::parse_message(String_ref message)
{
	Vector<String> split = cpputil::split_string(message, ' ');
	int unit_id = parse_int(split[0]);
	int job_id = parse_int(split[1]);
	if (print_jobs)
		print_line("unit_id=" + split[0] + ", job_id=" + split[1]);
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

void Jobsounds_app::print_help_text()
{
	print_line("Use the \"" + config_filename + "\" file to configurate.");
	print_line("Configuration settings and commands can also be passed as arguments.");
	print_line("");
	print_line("Available commands:");
	arg_parser.commands.foreach([](String_ref key, const Arg_parser::Command & command)
	{
		print_line(" " + key + ": " + command.description);
	});
	print_line("");
	print_line("Available settings:");
	arg_parser.settings.foreach([](String_ref key, const Arg_parser::Setting & setting)
	{
		print_line(" " + key + ": " + setting.description);
	});
	print_line("");
	print_line("Sounds can be configurate with comma-separated values, either as arguments or in the configuration file. See \"" + config_filename + "\" for details.");
}
