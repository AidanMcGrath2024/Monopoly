cmake_minimum_required(VERSION 3.22) # Specify CMake version.
project(homework02
    DESCRIPTION "Monopoly"
    VERSION 0.0.1) # A project name. This can be anything.
set(CMAKE_CXX_STANDARD 17) # Specify C++ version.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # To print something.
find_package(OpenGL REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/sfml_lib/install")
find_package(SFML 2.6.2 COMPONENTS graphics window system)
include_directories("${PROJECT_SOURCE_DIR}/third_party/sfml_lib/install/include")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)
# Create a binary file. 
# The first argument is the name of the binary file.
# It can be anything. In this case, it is set to be the project name.
# The other arguments are source files.
# Header files are not needed in add_executable(), assuming they are properly included.
add_executable(main main/main.cpp ${all_SRCS})

target_link_libraries(main m)
target_link_libraries(main sfml-graphics sfml-window sfml-system)
