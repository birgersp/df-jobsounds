#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "TCP_Connection.h"
#include "core.h"

#include <string>

#ifdef OS_WINDOWS
#include <Winsock2.h>
#else
#include <arpa/inet.h>
#endif

class TCP_Server
{
public:
    TCP_Server();
    ~TCP_Server();

    void bind(int port);
    bool is_bound();

    TCP_Connection accept_connection();

private:
    struct sockaddr_in socket_address;
    int socket_fd;
};

#endif // TCP_SERVER_H
