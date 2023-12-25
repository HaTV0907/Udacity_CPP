cmake_minimum_required(VERSION 3.11.3)
set(CMAKE_CXX_STANDARD 17)

project(hatvsbot)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB project_SRCS src/*.cpp)

add_executable(hatvsbot ${project_SRCS})

target_link_libraries(hatvsbot ${wxWidgets_LIBRARIES})

target_include_directories(hatvsbot PRIVATE include)
target_include_directories(hatvsbot PRIVATE ${wxWidgets_INCLUDE_DIRS})
