#include <iostream>
#include <arpa/inet.h>
#include "service/server.hpp"
#include "service/service-exception.hpp"

int main(int argc, char const* argv[]) {
    in_port_t port = htons(argc == 2 ? std::atoll(argv[1]) : 8080);

    try {
        echo_service::server sv(port);
        sv.echo();
    } catch (const echo_service::service_exception& e) {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}
