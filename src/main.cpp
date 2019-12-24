/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "core.h"
#include "Sound_Mixer.h"
#include "Socket_Server.h"
#include "util.h"
#include "Jobsounds_app.h"

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
		Vector<String> arguments;
		for (int i = 1; i < argc; i++)
			arguments.push_back(String(argv[i]));
		Jobsounds_app app;
		app.run(arguments);
	}
	catch (Exception e)
	{
		std::cerr << e.get_reason() << std::endl;
	}

	return 0;
}
