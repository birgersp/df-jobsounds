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

class Jobsounds_app
{
public:

	void run(const Vector<String>& arguments);

private:

	struct
	{
		bool enable = false;
		int job_id;
	} demo;

	uint port = 56730;
	String config_filename = "config.txt";
	Socket_Server server;
	cpputil::Map<int, Vector<Sound>> job_sounds;
	Sound_interval_manager inteval_manager;
	Sound_Mixer sound_mixer;
	void load_config();
	void parse_argument(String_ref argument);
	void process_connection(Socket_Connection& connection);
	void parse_message(String_ref message);
	void process_unit_job(int unit_id, int job_id);
	void run_demo();
	void run_server();

};

#endif /* JOBSOUNDS_APP_H */
