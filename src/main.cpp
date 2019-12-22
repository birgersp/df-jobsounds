/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "core.h"
#include "Sound_Mixer.h"
#include "Socket_Server.h"
#include "util.h"

#ifdef OS_WINDOWS
#include <winsock2.h>
#endif
#include <iostream>
#include <cpputil/timing.hpp>
#include <cpputil/errorhandling.hpp>

int main(int argc, char **argv)
{
	try
	{
		Sound_Mixer sound_mixer;
		sound_mixer.initialize();
		Sound sound = sound_mixer.load_sound("bin/dig.wav");
		sound_mixer.play(sound);

		Socket_Server server;
		server.bind(56730);
		print_line("waiting for connection");
		auto connection = server.accept_connection();
		print_line("connection established");
		std::string msg;
		while (not connection.is_closed())
		{
			msg.clear();
			connection.readline(msg);
			std::cout << get_millisec() << ": " << msg << std::endl;
		}
	}
	catch (Exception e)
	{
		std::cerr << e.to_string() << std::endl;
	}

	return 0;
}
