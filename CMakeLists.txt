cmake_minimum_required(VERSION 3.5)

project(time_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(time_client main.cpp
    client.h client.cpp)

include(GNUInstallDirs)
install(TARGETS time_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
