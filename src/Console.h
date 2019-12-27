/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

class Console
{
public:

	Console();
	void hide();
	void show();

private:

	HWND window_handle;

};

#endif /* CONSOLE_H */
