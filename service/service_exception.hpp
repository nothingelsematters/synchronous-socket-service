#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

namespace echo_service {

static const std::string PREFIX = "Failed to ";

class service_exception : public std::runtime_error {
public:
    service_exception(const std::string& what_arg) : std::runtime_error(PREFIX + what_arg) {}
    service_exception(const char* what_arg) : std::runtime_error(PREFIX + what_arg) {}
};

} /* echo_service */


#endif /* end of include guard: EXCEPTIONS_HPP */
