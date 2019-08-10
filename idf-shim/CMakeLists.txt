set(
    COMPONENT_SRCS
    firmware.c
)

register_component()

target_link_libraries(${COMPONENT_NAME} ${FIRMWARE_LIB})
