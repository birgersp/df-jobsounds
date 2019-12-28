/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef JOBSOUNDS_APP_H
#define JOBSOUNDS_APP_H

#include "core.h"
#include "Socket_Server.h"
#include "Sound.h"
#include "Sound_interval_manager.h"
#include "Sound_Mixer.h"
#include "Script_installer.h"
#include "Arg_parser.h"
#include "Console.h"
#include "Sound_loader.h"

class Jobsounds_app
{
public:

	Jobsounds_app();
	void run(const Vector<String>& arguments);

private:

	struct
	{
		bool enable = false;
		int job_id;
	} demo;

	bool print_jobs = false;
	uint port = 56730;
	String config_filename = "config.txt";
	bool noinstall = false;
	bool hide = false;
	bool debug = false;
	Socket_Server server;
	Map<int, Vector<Sound>> job_sounds;
	Sound_interval_manager inteval_manager;
	Sound_Mixer sound_mixer;
	Script_installer script_installer;
	Arg_parser arg_parser;
	Console console;
	Sound_loader sound_loader;

	void run_app(const Vector<String>& arguments);
	void load_config();
	void parse_argument(String_ref argument);
	void process_connection(Socket_Connection& connection);
	void parse_message(String_ref message);
	void process_unit_job(int unit_id, int job_id);
	void run_demo();
	void run_server();
	void print_help_text();
	void debug_print(String_ref string);

};

#endif /* JOBSOUNDS_APP_H */
