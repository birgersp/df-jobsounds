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
#include "util.h"

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

    // Initialize Winsock
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        throw functionException("WSAStartup failed: " + get_wsa_error_string());
    }

    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    struct addrinfo *result = NULL;
    if (getaddrinfo(NULL, "56730", &hints, &result) != 0)
    {
        WSACleanup();
        throw functionException("getaddrinfo failed: " + get_wsa_error_string());
    }

    // Create a SOCKET for connecting to server
    SOCKET listen_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listen_socket == INVALID_SOCKET)
    {
        std::string error = get_wsa_error_string();
        freeaddrinfo(result);
        WSACleanup();
        throw functionException("socket failed: " + error);
    }

    if (::bind(listen_socket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
    {
        std::string error = get_wsa_error_string();
        freeaddrinfo(result);
        closesocket(listen_socket);
        WSACleanup();
        throw functionException("bind failed: " + error);
    }

    freeaddrinfo(result);

    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::string error = get_wsa_error_string();
        closesocket(listen_socket);
        WSACleanup();
        throw functionException("listen failed: " + error);
    }

    if (accept(listen_socket, NULL, NULL) == INVALID_SOCKET)
    {
        std::string error = get_wsa_error_string();
        closesocket(listen_socket);
        WSACleanup();
        throw functionException("accept failed: " + error);
    }

    SOCKET client_socket;
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
