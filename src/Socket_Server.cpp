#include "Socket_Server.h"

#include <cpputil/errorhandling.hpp>
#include <cstring>
#include <chrono>
#include <csignal>
#include <unistd.h>
#include <string>
#include "util.h"

Socket_Server::Socket_Server()
{
}

Socket_Server::~Socket_Server()
{
	if (is_bound())
		closesocket(listen_socket);
	WSACleanup();
}

void Socket_Server::bind(int port)
{
	if (is_bound())
		throw function_exception("Already bound");

	// Initialize Winsock
	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
	{
		throw function_exception("WSAStartup failed: " + get_wsa_error_string());
	}

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	struct addrinfo *result = NULL;
	char port_string[6];
	itoa(port, port_string, 10);
	if (getaddrinfo(NULL, port_string, &hints, &result) != 0)
	{
		throw function_exception("getaddrinfo failed: " + get_wsa_error_string());
	}

	// Create a SOCKET for connecting to server
	listen_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listen_socket == INVALID_SOCKET)
	{
		std::string error = get_wsa_error_string();
		freeaddrinfo(result);
		throw function_exception("socket failed: " + error);
	}

	if (::bind(listen_socket, result->ai_addr, (int) result->ai_addrlen) == SOCKET_ERROR)
	{
		std::string error = get_wsa_error_string();
		freeaddrinfo(result);
		throw function_exception("bind failed: " + error);
	}
	freeaddrinfo(result);

	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::string error = get_wsa_error_string();
		throw function_exception("listen failed: " + error);
	}
}

bool Socket_Server::is_bound()
{
	return listen_socket != INVALID_SOCKET;
}

Socket_Connection Socket_Server::accept_connection()
{
	if (!is_bound())
		throw function_exception("Socket not bound");

	SOCKET client_socket = accept(listen_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
	{
		std::string error = get_wsa_error_string();
		throw function_exception("accept failed: " + error);
	}

	return Socket_Connection(client_socket);
}
