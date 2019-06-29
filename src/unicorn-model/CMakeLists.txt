set(
    COMPONENT_SRCS
    src/error.cpp
)

set(
    COMPONENT_ADD_INCLUDEDIRS
    include
)

set(
    COMPONENT_REQUIRES
    exl-component
    unicorn-colors
)


register_component()