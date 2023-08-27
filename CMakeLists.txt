cmake_minimum_required(VERSION 3.10)
project(Sem-2_C_Project_Work)

# Add the executable target
add_executable(test test.c)

# Specify the include directory for external headers
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/include)
