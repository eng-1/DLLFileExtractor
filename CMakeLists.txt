cmake_minimum_required(VERSION 3.13)
project(DLLFileExtractor)

set(CMAKE_CXX_STANDARD 14)

add_executable(DLLFileExtractor main.cpp PELocator.cpp PELocator.h FileFormats.h FileWriter.cpp FileWriter.h)