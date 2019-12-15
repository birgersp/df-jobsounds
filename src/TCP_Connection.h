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
    std::string readline();

private:
    const SOCKET socket;
    static const uint buffer_length = 512;
    char buffer[buffer_length];
};

#endif /* TCP_CONNECTION_H */
