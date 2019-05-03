#include <stdio.h>
#include <arpa/inet.h>
#include "service/server.hpp"
#include "service/service_exception.hpp"

int main(int argc, char const* argv[]) {
    in_port_t port = htons(argc == 2 ? std::atoll(argv[1]) : 8080);

    try {
        echo_service::server sv(port);
        sv.echo();
    } catch (const echo_service::service_exception& e) {
        perror(e.what());
        return 1;
    }
    return 0;
}
