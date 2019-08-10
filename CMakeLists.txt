cmake_minimum_required(VERSION 3.12)

set(
    FIRMWARE_LIB
    "${CMAKE_CURRENT_SOURCE_DIR}/firmware/target/xtensa-esp8266-none-elf/release/libfirmware.a"
)

set(EXTRA_COMPONENT_DIRS "idf-shim")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(shelter-unicorn)
