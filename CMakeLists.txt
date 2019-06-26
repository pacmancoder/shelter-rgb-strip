cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

# ESP8266 IDF initialization
set(
    EXTRA_COMPONENT_DIRS
    src/idf-components/bootstrapper
    src/colors
)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(shelter_rgb_strip)