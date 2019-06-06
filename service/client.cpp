#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client.hpp"
#include "service-exception.hpp"

namespace echo_service {

client::client(uint32_t address, in_port_t port)
    : address(address), port(port), sockfd(socket(AF_INET, SOCK_STREAM, 0)), rdr(sockfd) {

    check_throw(sockfd, "create socket");

    sockaddr_in addr;
    const socklen_t addr_size = sizeof(sockaddr_in);
    memset(&addr, 0, addr_size);

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = address;

    check_throw(connect(sockfd, reinterpret_cast<sockaddr*>(&addr), addr_size), "connect");
}

client::~client() {
    close(sockfd);
}

std::string client::yell(const std::string& str) {
    send_message(sockfd, str);
    auto [success, message] = rdr.read();
    check_throw(success, "read");
    return message;
}

} /* echo_service */
