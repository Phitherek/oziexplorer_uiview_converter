cmake_minimum_required(VERSION 3.3)
project(oziexplorer_uiview_converter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Converter.cpp Converter.h ConversionError.cpp ConversionError.h)
add_executable(oziexplorer_uiview_converter ${SOURCE_FILES})