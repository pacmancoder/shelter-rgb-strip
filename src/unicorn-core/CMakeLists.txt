set(
    COMPONENT_SRCS
    src/static_color_sample_provider.cpp
    src/shared_color_sample_provider.cpp
    src/Renderer.cpp
)

set(
    COMPONENT_ADD_INCLUDEDIRS
    include
)

set(
    COMPONENT_REQUIRES
    unithread
    unicorn-model
    unicorn-hal
)


register_component()