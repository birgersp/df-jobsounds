#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include "core.h"

#include <winsock2.h>
#include <string>

class TCP_Connection
{
public:
	TCP_Connection(SOCKET socket);
	~TCP_Connection();
	void readline(Mutable_String_Ref string);
	bool is_closed() const;

private:
	const SOCKET socket;
	bool connection_open = true;
	static const uint BUFFER_SIZE = 128;
	char buffer[BUFFER_SIZE];
};

#endif /* TCP_CONNECTION_H */
