#include "TCP_Server.h"

#ifdef OS_WINDOWS
#include <ws2tcpip.h>
#endif

#include <cpputil/errorhandling.hpp>
#include <cstring>
#include <chrono>
#include <csignal>
#include <unistd.h>
#include <string>

TCP_Server::TCP_Server() : socket_fd(-1)
{
}

TCP_Server::~TCP_Server()
{
    if (is_bound())
        close(socket_fd);
}

void TCP_Server::bind(int port)
{
    if (is_bound())
        throw functionException("Already bound");

    fflush(stdout);

    // Initial socket binding
    char optval = 1;
    struct sockaddr_in serv_addr;
    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0)
        throw functionException("Could not open socket");

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0)
        throw functionException("Could not set socket options");

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_UNIX;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (::bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        throw functionException("Binding port " + std::to_string(port) + " failed");
    else
    {
        listen(socket_fd, 5);
        signal(13, SIG_IGN);
    }
}

bool TCP_Server::is_bound()
{
    return socket_fd >= 0;
}

TCP_Connection TCP_Server::accept_connection()
{
    if (!is_bound())
        throw functionException("Socket not bound");

    // Accepting connection
    socklen_t clilen;
    clilen = sizeof(socket_address);

    int newsockfd = accept(socket_fd, (struct sockaddr *)&socket_address, &clilen);
    return TCP_Connection(newsockfd);
}
