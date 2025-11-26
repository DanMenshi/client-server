cmake_minimum_required(VERSION 3.19)
project(boost_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(server
    server_main.cpp
    session.cpp session.h
)
target_link_libraries(server
    PRIVATE
        Qt::Core
        Boost::boost
)

qt_add_executable(client
    client_main.cpp
    file_trader.cpp file_trader.h
    client.cpp client.h
    file_header.h
    constant.h
)
target_link_libraries(client
    PRIVATE
        Qt::Core
        Boost::boost
)
