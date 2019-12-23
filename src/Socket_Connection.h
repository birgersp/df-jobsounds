/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H

#include "core.h"

#include <winsock2.h>
#include <string>

class Socket_Connection
{
public:
	Socket_Connection(SOCKET socket);
	~Socket_Connection();
	void readline(Mutable_string_ref string);
	bool is_closed() const;

private:
	const SOCKET socket;
	bool connection_open = true;
	static const uint BUFFER_SIZE = 128;
	char buffer[BUFFER_SIZE];
};

#endif /* SOCKET_CONNECTION_H */
