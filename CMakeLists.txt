cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
    main.cpp
    src/storage.cpp
    src/tcpserver.cpp
    src/server.cpp
    src/threadPool.cpp
    src/msgHandler.cpp
    src/commands.cpp
)

add_executable(server ${SOURCES})

target_link_libraries(server)