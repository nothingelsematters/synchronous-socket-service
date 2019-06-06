#include <string>
#include <iostream>
#include <arpa/inet.h>
#include "service/client.hpp"
#include "service/service-exception.hpp"

int main(int argc, char const* argv[]) {
    uint32_t address = inet_addr("127.0.0.1");
    in_port_t port = htons(8080);
    std::string claim = "standard claim";

    switch (argc) {
        case 4: claim = argv[3];
        case 3: address = inet_addr(argv[2]);
        case 2: port = htons(std::atoll(argv[1]));
    }

    try {
        echo_service::client cn(address, port);
        std::cout << cn.yell(claim + "_1") << '\n'
                  << cn.yell(claim + "_2") << '\n';
    } catch (const echo_service::service_exception& e) {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}
