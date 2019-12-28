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
#include "Console.h"
#include <cpputil/Table_printer.hpp>

Jobsounds_app::Jobsounds_app() :
sound_loader(sound_mixer)
{
	arg_parser.add_command("help", [this]()
	{
		print_help_text();
		throw function_exception("Aborted");
	}, "View help text");

	arg_parser.add_command("noinstall", [this]()
	{
		noinstall = true;
	}, "Skip jobsounds script installation in DFHack directory");

	arg_parser.add_command("print-jobs", [this]()
	{
		print_jobs = true;
	}, "Print the unit and job id when such data is received from Dwarf Fortress");

	arg_parser.add_command("hide", [this]()
	{
		hide = true;
	}, "Hide the console window once the server is started. The console window will re-appear if an error occurs");

	arg_parser.add_command("debug", [this]()
	{
		debug = true;
	}, "Enable debug mode");

	arg_parser.add_setting("demo", [this](String_ref string)
	{
		demo.enable = true;
		demo.job_id = parse_int(string);
	}, "Loop a job to test how the sounds loaded for that job sounds. Example: demo=68");

	arg_parser.add_setting("dfdir", [this](String_ref string)
	{
		script_installer.df_dir = string;
	}, "Explicitly set the Dwarf Fortress directory. Use this if you did not install jobsounds in the Dwarf Fortress folder. Example: dfdir=\"C:\\Dwarf Fortress\\\"");
}

void Jobsounds_app::run(const Vector<String>& arguments)
{
	try
	{
		run_app(arguments);
	}
	catch (const Exception& exception)
	{
		console.show();
		print_error("Error: " + exception.get_reason());
		print_line("Use command \"help\" to view help text");
		wait_for_enter();
		throw exception;
	}
}

void Jobsounds_app::run_app(const Vector<String>& arguments)
{
	print_line("Dwarf Fortress sound utility");
	print_line("Programmed by birgersp");
	print_line("Visit https://github.com/birgersp/df-jobsounds");
	print_line("");

	if (vector_contains(arguments, String("help")))
	{
		print_help_text();
		return;
	}

	print_line("Use the \"help\" command to view available commands and settings");
	print_line("Edit the \"" + config_filename + "\" file to configurate");
	print_line("");

	sound_mixer.initialize();
	srand(time(nullptr));

	try
	{
		load_config();
	}
	catch (const Exception& exception)
	{
		throw function_exception("Failed to load configuration: " + config_filename + ". " + exception.get_reason());
	}

	for (String_ref argument : arguments)
	{
		try
		{
			parse_argument(argument);
		}
		catch (const Exception& exception)
		{
			throw function_exception("Failed to parse argument: " + argument + "\n" + exception.get_reason());
		}
	}

	if (job_sounds.size() == 0)
	{
		print_line("Warning: no sounds loaded");
	}

	if (not noinstall)
		script_installer.install_script();

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
	print_line("Loading \"" + config_filename + "\"");
	Vector<String> lines = read_file_lines(config_filename);
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
				catch (const Exception& exception)
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
		Vector<String> comma_split = split_string(argument, ',');
		if (comma_split.size() != 3)
		{
			throw function_exception("Invalid syntax");
		}
		print_line(argument);
		int job_id = parse_int(comma_split[0]);
		String dirname = comma_split[1];
		int min_time = parse_int(comma_split[2]);
		if (job_sounds.get(job_id) != nullptr)
		{
			print_line("Warning: sounds are already added for job " + to_string(job_id) + ". These sounds will be unloaded");
		}
		print_line("Loading sounds for job: " + to_string(job_id));
		Vector<Sound> sounds;
		sound_loader.load_wavs(dirname, sounds);
		job_sounds.put(job_id, sounds);
		inteval_manager.set_sound_interval(job_id, min_time);
	}
	else if (str_contains(argument, '='))
	{
		print_line(argument);
		arg_parser.parse_as_setting(argument);
	}
	else
	{
		print_line(argument);
		arg_parser.parse_as_command(argument);
	}
}

void Jobsounds_app::process_connection(Socket_Connection& connection)
{
	String message;
	bool connection_closed = false;
	while (not connection_closed)
	{
		debug_print("Reading message");
		message.clear();
		connection.readline(message);
		if (connection.is_closed())
			connection_closed = true;
		else
		{
			debug_print("Read: " + message);
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
	print_line("Connection closed");
}

void Jobsounds_app::parse_message(String_ref message)
{
	Vector<String> split = split_string(message, ' ');
	if (split.size() != 2)
	{
		throw function_exception("Cannot parse message: " + message);
	}
	int unit_id = parse_int(split[0]);
	int job_id = parse_int(split[1]);
	if (print_jobs or debug)
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
		debug_print("Playing sound for job: " + to_string(job_id));
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
		sleep_mS(20);
	}
}

void Jobsounds_app::run_server()
{
	print_line("Starting server");
	server.bind(port);
	if (hide)
		console.hide();
	while (true)
	{
		print_line("Waiting for a connection");
		auto connection = server.accept_connection();
		print_line("Connection established");
		print_line("Now playing sound as job data is sent from DF");
		process_connection(connection);
	}
}

void Jobsounds_app::print_help_text()
{
	Table_printer table_printer;
	print_line("Edit the \"" + config_filename + "\" file to configurate");
	print_line("Configuration settings and commands can also be passed as arguments");
	table_printer.clear();
	arg_parser.commands.foreach([&table_printer](String_ref key, const Arg_parser::Command & command)
	{
		table_printer.add_row({" " + key, ": " + command.description});
	});
	print_line("");
	print_line("Available commands:");
	print_line(table_printer.to_string());
	table_printer.clear();
	arg_parser.settings.foreach([&table_printer](String_ref key, const Arg_parser::Setting & setting)
	{
		table_printer.add_row({" " + key, ": " + setting.description});
	});
	print_line("");
	print_line("Available settings:");
	print_line(table_printer.to_string());
	print_line("");
	print_line("Sounds can be configurate with comma-separated values, either as arguments or in the configuration file. See \"" + config_filename + "\" for details");
}

void Jobsounds_app::debug_print(String_ref string)
{
	if (not debug)
		return;
	print_line(string);
}
