cmake_minimum_required(VERSION 2.8.11)
project(synchronous-socket-service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(server main-server.cpp)
add_executable(client main-client.cpp)

add_library(common STATIC service/service-exception.hpp service/utils.hpp)
add_library(serverlib STATIC service/server.hpp service/server.cpp)
add_library(clientlib STATIC service/client.hpp service/client.cpp)
set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(server serverlib common)
target_link_libraries(client clientlib common)
