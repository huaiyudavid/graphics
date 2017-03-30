cmake_minimum_required(VERSION 3.6)
project(graphics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CLI.h Command.h Tokenizer.h Tokenizer.cpp CLI.cpp MoveCommand.h MoveCommand.cpp Command.cpp DrawCommand.h DrawCommand.cpp ColorCommand.h ColorCommand.cpp ReadCommand.h ReadCommand.cpp TiffStatCommand.h TiffStatCommand.cpp Utilities.cpp Utilities.h TiffReadCommand.h TiffReadCommand.cpp TiffImageData.h TiffImageData.cpp global.h TiffWriteCommand.h TiffWriteCommand.cpp ResizeCommand.h ResizeCommand.cpp Filter.h Filter.cpp Matrix44.h Matrix44.cpp Vector4.h Vector4.cpp Vector3.h Vector3.cpp PushCommand.cpp PushCommand.h PopCommand.cpp PopCommand.h TranslateCommand.cpp TranslateCommand.h ScaleCommand.cpp ScaleCommand.h RotateCommand.cpp RotateCommand.h OrthoCommand.cpp OrthoCommand.h PerspectiveCommand.cpp PerspectiveCommand.h LookatCommand.cpp LookatCommand.h lines.cpp)
add_executable(graphics ${SOURCE_FILES})