cmake_minimum_required(VERSION 2.8.11)
project(synchronous-socket-service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(SERVER "service/server")
set(CLIENT "service/client")
set(COMMON "service/service_exception.hpp")

add_executable(server ${COMMON} ${SERVER}.cpp ${SERVER}.hpp main-server.cpp)
add_executable(client ${COMMON} ${CLIENT}.cpp ${CLIENT}.hpp main-client.cpp)
