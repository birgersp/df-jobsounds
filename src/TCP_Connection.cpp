#include "TCP_Connection.h"
#include "util.h"

#include <cpputil/errorhandling.hpp>

TCP_Connection::TCP_Connection(SOCKET socket) : socket(socket)
{
}

TCP_Connection::~TCP_Connection()
{
    closesocket(socket);
}

std::string TCP_Connection::readline()
{
    std::string read_buffer;
    int result;
    do
    {
        int result = recv(socket, buffer, buffer_length, 0);
        std::cout << result << std::endl;
        read_buffer += std::string(buffer);
    } while (result > 0);

    if (result < 0)
    {
        throw functionException("Receive failed: " + get_wsa_error_string());
    }
    return read_buffer;
}
