cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
project(Game-of-Life)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/ CACHE PATH "Output directory of all executables.")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system program_options)

add_executable(main cells_grid.cpp main.cpp)
target_link_libraries(main ${OpenCV_LIBS} ${Boost_LIBRARIES})