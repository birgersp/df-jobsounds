#include <unistd.h>
#include <cpputil/errorhandling.hpp>

#include "TCP_Connection.h"

TCP_Connection::TCP_Connection(int fd) : file_descriptor(fd)
{
}

TCP_Connection::~TCP_Connection()
{
    close(file_descriptor);
}

std::string TCP_Connection::readline()
{
    std::string read_buffer;

    int n;
    char character;
    bool reading = true;
    while (reading)
    {
        n = read(file_descriptor, &character, 1);
        if (n < 0)
            throw functionErrorException();
        else if (n > 0)
        {
            if (character == '\n')
                reading = false;
            else
                read_buffer += character;
        }
        else
        {
            throw functionErrorException();
            reading = false;
        }
    }

    return read_buffer;
}
