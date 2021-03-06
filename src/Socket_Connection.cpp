/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Socket_Connection.h"
#include "util.h"

#include <cpputil/errorhandling.hpp>

Socket_Connection::Socket_Connection(SOCKET socket) : socket(socket)
{
}

Socket_Connection::~Socket_Connection()
{
	closesocket(socket);
}

void Socket_Connection::readline(Mutable_string_ref string)
{
	if (is_closed())
		throw function_exception("Connection closed");

	int n;
	bool done = false;
	while (not done)
	{
		n = recv(socket, buffer, BUFFER_SIZE, 0);
		if (n < 0)
			throw function_exception("Read error: " + get_wsa_error_string());
		else if (n == 0)
		{
			connection_open = false;
			done = true;
		}
		else
		{
			string += String(buffer, n);
			if (buffer[n - 1] == '\n')
				done = true;
		}
	}
}

bool Socket_Connection::is_closed() const
{
	return !connection_open;
}
