#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "service-exception.hpp"

namespace echo_service {

static bool valid(int arg) {
    return arg != -1;
}

static bool check(const int arg, const std::string& message) {
    if (!valid(arg)) {
        perror(message.c_str());
        return false;
    }
    return true;
}

static void check_throw(const int arg, const std::string& message) {
    if (!valid(arg)) {
        throw service_exception(message);
    }
}

static const std::string BOUNDARY = "\r\n";

class reader {
public:
    reader(int sockfd) : sockfd(sockfd) {}

    std::pair<int, std::string> read() {
        int read = 0;

        while (true) {
            std::string::size_type boundary = storage.find(BOUNDARY);
            if (boundary != std::string::npos) {
                std::string message = storage.substr(0, boundary);
                storage = storage.substr(boundary + BOUNDARY.size());
                return {message.size(), message};
            }

            char buffer[BUFFER_SIZE] = {};
            ssize_t iter_read = ::read(sockfd, buffer, BUFFER_SIZE);
            if (!valid(iter_read)) {
                return {-1, ""};
            }
            read += iter_read;
            std::string append(buffer);
            if (append.empty()) {
                return {0, ""};
            }
            storage += append;
        }
    }

private:
    static constexpr size_t BUFFER_SIZE = 1024;
    const int sockfd;
    std::string storage;
};

static void send_message(const int sockfd, const std::string& message, const bool error_termination = true) {
    const std::string message_to_send = message + BOUNDARY;
    const char* cstr = message_to_send.c_str();
    const size_t size = strlen(cstr);
    size_t sent = 0;

    while (sent < size) {
        ssize_t iter_sent = send(sockfd, cstr + sent, size - sent, 0);
        const std::string errormsg = "send";
        if (error_termination) {
            check_throw(iter_sent, errormsg);
        } else {
            check(iter_sent, errormsg);
        }
        sent += static_cast<size_t>(iter_sent);
    }
}

} /* echo_service */


#endif /* end of include guard: UTILS_HPP */
