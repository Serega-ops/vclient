cmake_minimum_required(VERSION 3.16)
project(vclient CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Boost REQUIRED COMPONENTS program_options)
add_library(vclient_core
    src/interface.cpp
    src/data_reader.cpp
    src/data_writer.cpp
    src/authenticator.cpp
    src/communicator.cpp
)
target_include_directories(vclient_core PUBLIC include)
target_link_libraries(vclient_core PUBLIC Boost::program_options cryptopp pthread)
add_executable(vclient src/main.cpp)
target_link_libraries(vclient PRIVATE vclient_core)
enable_testing()
add_executable(vclient_tests tests/test_main.cpp)
target_link_libraries(vclient_tests PRIVATE vclient_core UnitTest++)
add_test(NAME all_tests COMMAND vclient_tests)
