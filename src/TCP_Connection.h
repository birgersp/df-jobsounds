#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <string>

class TCP_Connection
{
public:
    TCP_Connection(int fd);
    ~TCP_Connection();
    std::string readline();

private:
    const int file_descriptor;
};

#endif /* TCP_CONNECTION_H */
