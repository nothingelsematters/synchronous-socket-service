#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.hpp"
#include "service-exception.hpp"
#include "utils.hpp"


namespace echo_service {

server::server(in_port_t port) : port(port), sockfd(socket(AF_INET, SOCK_STREAM, 0)) {
    check_throw(sockfd, "create socket");
}

server::~server() {
    close(sockfd);
}


void server::echo() {
    std::cout << "starting" << '\n';
    sockaddr_in addr;
    socklen_t addr_size = sizeof(sockaddr_in);
    memset(&addr, 0, sizeof(sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = HOME_ADDR;

    check_throw(bind(sockfd, reinterpret_cast<sockaddr*>(&addr), addr_size), "bind");
    check_throw(listen(sockfd, BACKLOG), "listen");

    while (true) {
        sockaddr_in client;
        socklen_t csize;

        int receivedfd = accept(sockfd, reinterpret_cast<sockaddr*>(&client), &csize);
        if (!check(receivedfd, "accept")) {
            close(receivedfd);
            continue;
        }

        reader rdr(receivedfd);
        while (true) {
            auto [read_count, message] = rdr.read();
            if (!check(read_count, "read")) {
                close(receivedfd);
                break;
            }
            if (!read_count) {
                break;
            }

            send_message(receivedfd, message, false);
        }

        close(receivedfd);
    }
}

} /* echo_service */
