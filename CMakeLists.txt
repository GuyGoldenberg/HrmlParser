cmake_minimum_required(VERSION 3.8)
project(hrml_parser)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES hrml_parser.cpp validator.cpp validator.h utils.h hrml_token.cpp hrml_token.h hrml.cpp hrml.h)
add_executable(hrml_parser ${SOURCE_FILES})
