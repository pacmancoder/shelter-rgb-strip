set(
    COMPONENT_SRCS
    src/StaticColorSampleProvider.cpp
)

set(
    COMPONENT_ADD_INCLUDEDIRS
    include
)

set(
    COMPONENT_REQUIRES
    exl-component
    colors
)


register_component()