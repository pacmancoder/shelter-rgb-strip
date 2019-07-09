set(
    COMPONENT_SRCS
    # Model
    ../shelter-core/shelter-model/src/shelter-model/device_descriptor.cpp
    # Utils
    ../shelter-core/shelter-utils/src/buffer_writer.cpp
    ../shelter-core/shelter-utils/src/buffer_reader.cpp
    ../shelter-core/shelter-utils/src/crc8.cpp
    ../shelter-core/shelter-utils/src/base64.cpp
    ../shelter-core/shelter-utils/src/ssid_device_descriptor.cpp
)

set(
    COMPONENT_REQUIRES
    exl-component
)

set(
    COMPONENT_ADD_INCLUDEDIRS
    ../shelter-core/shelter-model/include
    ../shelter-core/shelter-utils/include
)

register_component()