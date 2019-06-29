cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

# ESP8266 IDF initialization
set(
    EXTRA_COMPONENT_DIRS
    # Third party library components
        src/libexl/exl-component
    # Core platform-agnostic components
    src/colors
    src/model
    # ESP-specific components
    src/idf-components/bootstrapper
)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(shelter_rgb_strip)