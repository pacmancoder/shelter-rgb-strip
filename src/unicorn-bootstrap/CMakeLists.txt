set(
    COMPONENT_SRCS
    src/entry_point.cpp
)

set(
    COMPONENT_REQUIRES
    unicorn-core
    unicorn-hal
)

register_component()