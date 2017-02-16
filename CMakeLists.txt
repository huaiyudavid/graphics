cmake_minimum_required(VERSION 3.6)
project(graphics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CLI.h Command.h Tokenizer.h Tokenizer.cpp CLI.cpp MoveCommand.h MoveCommand.cpp Command.cpp DrawCommand.h DrawCommand.cpp ColorCommand.h ColorCommand.cpp ReadCommand.h ReadCommand.cpp TiffStatCommand.h TiffStatCommand.cpp Utilities.cpp)
add_executable(graphics ${SOURCE_FILES})