cmake_minimum_required(VERSION 3.7)
project(mysql_manager)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp mysql_manager.cpp mysql_manager.h)
add_executable(mysql_manager ${SOURCE_FILES})
target_link_libraries(mysql_manager mysqlclient)