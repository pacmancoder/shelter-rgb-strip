set(
    COMPONENT_SRCS
    src/static_color_sample_provider.cpp
    src/shared_color_sample_provider.cpp
    src/spectrum_color_sample_provider.cpp
    src/breathing_color_sample_provider.cpp
    src/renderer.cpp
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