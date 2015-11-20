cmake_minimum_required(VERSION 3.3)
project(oziexplorer_uiview_converter)
string(TOLOWER ${CMAKE_BUILD_TYPE} _type)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Converter.cpp Converter.h ConversionError.cpp ConversionError.h)
set(CONVERSION_TEST_FILES Converter.h Converter.cpp ConversionError.h ConversionError.cpp ConversionTest.cpp)
add_executable(oziexplorer_uiview_converter ${SOURCE_FILES})
if(_type STREQUAL debug)
    add_executable(ConversionTest ${CONVERSION_TEST_FILES})
endif()