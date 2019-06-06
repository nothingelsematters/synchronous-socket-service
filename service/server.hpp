#ifndef SERVER_HPP
#define SERVER_HPP

#include <netinet/in.h>

namespace echo_service {

class server {
public:
    explicit server(in_port_t port);

    server(const server&) = delete;
    server& operator=(const server&) = delete;

    ~server();

    void echo();

private:
    const in_port_t port;
    const int sockfd;

    static constexpr int BACKLOG = 5; // max length to which the queue of pending connections may grow
    static constexpr uint32_t HOME_ADDR = (1 << 24) + 127; // home address
};

} /* echo_service */

#endif /* end of include guard: SERVER_HPP */
