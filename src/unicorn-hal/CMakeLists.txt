set(
    COMPONENT_SRCS
    src/rgb_strip.cpp
    src/rng.cpp
    src/event_manager.cpp
    src/module_initializers.cpp
    src/wifi.cpp
    src/device.cpp
)

set(
    COMPONENT_ADD_INCLUDEDIRS
    include
)

set(
    COMPONENT_REQUIRES
    tcpip_adapter
    nvs_flash
    unicorn-network-model
    unithread
)

register_component()