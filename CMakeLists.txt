cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

# ESP8266 IDF initialization
set(
    EXTRA_COMPONENT_DIRS
    # Third party library components
    src/libexl/exl-component
    # Universal components
    src/unithread
    # Core components
    src/unicorn-network-model
    src/unicorn-hal
    src/unicorn-colors
    src/unicorn-model
    src/unicorn-core
    src/unicorn-bootstrap
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(shelter_rgb_strip)