/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Jobsounds_app.h"

void Jobsounds_app::run(const Vector<String>& arguments)
{
	for (StringRef argument : arguments)
		parse_argument(argument);
	server.bind(port);
}

void Jobsounds_app::parse_argument(String_Ref argument)
{

}
