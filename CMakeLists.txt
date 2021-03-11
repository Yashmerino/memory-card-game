# CMakeList.txt : CMake project for Pexeso, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Pexeso")

add_subdirectory("3rdparty/SFML-2.5.1")

# Add source to this project's executable.
add_executable (Pexeso "Pexeso.cpp")

target_link_libraries(Pexeso sfml-audio sfml-window sfml-graphics sfml-system)

# TODO: Add tests and install targets if needed.
