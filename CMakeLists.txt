cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

set(EXTRA_COMPONENT_DIRS src/idf-components)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(shelter_rgb_strip)