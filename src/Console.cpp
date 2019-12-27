/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Console.h"

Console::Console()
{
	window_handle = GetConsoleWindow();
}

void Console::hide()
{
	ShowWindow(window_handle, SW_HIDE);
}

void Console::show()
{
	ShowWindow(window_handle, SW_SHOW);
}
