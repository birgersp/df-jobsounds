/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

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
