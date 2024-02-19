cmake_minimum_required(VERSION 3.25)
project(Gradebook_V2)

set(CMAKE_CXX_STANDARD 17)

# Include MyHTML headers
include_directories("C:/Users/maism/Documents/GitHub/myhtml/include")

add_executable(Gradebook_V2 main.cpp "Gradebook Aggregator.cpp" "Transcript Aggregator.cpp")

# Link MyHTML library
target_link_libraries(Gradebook_V2 "C:/Users/maism/Documents/GitHub/myhtml/source/myhtml/libmyhtml.dll")
