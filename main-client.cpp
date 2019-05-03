#include <string>
#include <arpa/inet.h>
#include "service/client.hpp"
#include "service/service_exception.hpp"

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
        cn.yell(claim + "_1");
        cn.yell(claim + "_2");
    } catch (const echo_service::service_exception& e) {
        perror(e.what());
        return 1;
    }
    return 0;
}
