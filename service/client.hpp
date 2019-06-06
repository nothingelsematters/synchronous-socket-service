#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <netinet/in.h>
#include "utils.hpp"

namespace echo_service {

class client {
public:
    explicit client(uint32_t address, in_port_t port);
    ~client();

    std::string yell(const std::string& str);

private:
    const uint32_t address;
    const in_port_t port;
    const int sockfd;
    reader rdr;
};

} /* echo_service */


#endif /* end of include guard: CLIENT_HPP */
