#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.hpp"
#include "service_exception.hpp"

namespace echo_service {

server::server(in_port_t port) : port(port), sockfd(socket(AF_INET, SOCK_STREAM, 0)) {
    if (sockfd == -1) {
        throw service_exception("create socket");
    }
}

server::~server() {
    close(sockfd);
}

void server::echo() {
    sockaddr_in addr;
    socklen_t addr_size = sizeof(sockaddr_in);
    memset(&addr, 0, sizeof(sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = HOME_ADDR;

    if (bind(sockfd, reinterpret_cast<sockaddr*>(&addr), addr_size) == -1) {
        throw service_exception("bind");
    }

    if (listen(sockfd, BACKLOG) == -1) {
        throw service_exception("listen");
    }

    while (true) {
        sockaddr_in client;
        socklen_t csize;

        int receivedfd = accept(sockfd, reinterpret_cast<sockaddr*>(&client), &csize);
        if (receivedfd == -1) {
            perror("Failed to accept");
            close(receivedfd);
            continue;
        }

        char buffer[BUFFER_SIZE] = {};
        int nread = read( receivedfd , buffer, BUFFER_SIZE);
        if (nread == -1) {
            perror("Failed to read");
            close(receivedfd);
            continue;
        }

        if (send(receivedfd , buffer , nread, 0) != nread) {
            perror("Failed to send");
        }

        close(receivedfd);
    }
}

} /* echo_service */
