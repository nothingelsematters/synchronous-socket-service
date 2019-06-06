#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include "string.h"

namespace echo_service {

static const std::string PREFIX = "Failed to ";

class service_exception : public std::runtime_error {
public:
    service_exception(const std::string& what_arg) : std::runtime_error(message(what_arg)) {}
    service_exception(const char* what_arg) : std::runtime_error(message(what_arg)) {}

private:
    static std::string message(const std::string& arg) {
        return PREFIX + arg + ": " + strerror(errno);
    }
};

} /* echo_service */


#endif /* end of include guard: EXCEPTIONS_HPP */
