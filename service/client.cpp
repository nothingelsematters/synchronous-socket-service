#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client.hpp"
#include "service_exception.hpp"

namespace echo_service {

client::client(uint32_t address, in_port_t port) : address(address), port(port) {}

client::~client() {
    close(sockfd);
}

void client::yell(const std::string& str) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        throw service_exception("create socket");
    }

    sockaddr_in addr;
    const socklen_t addr_size = sizeof(sockaddr_in);
    memset(&addr, 0, addr_size);

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = address;

    if (connect(sockfd, reinterpret_cast<sockaddr*>(&addr), addr_size) == -1) {
        throw service_exception("connect");
    }

    const char* cstr = str.c_str();
    size_t cstrlen = strlen(cstr);
    if (send(sockfd, cstr, cstrlen, 0) != cstrlen) {
        throw service_exception("send");
    }

    char buffer[BUFFER_SIZE] = {};
    if (read(sockfd, buffer, BUFFER_SIZE) == -1) {
        throw service_exception("read");
    }

    printf("%s\n", buffer);
}


} /* echo_service */
