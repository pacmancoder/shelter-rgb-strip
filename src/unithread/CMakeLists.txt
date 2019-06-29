set(
    COMPONENT_SRCS
    src/mutex.cpp
    src/thread.cpp
)

set(
    COMPONENT_ADD_INCLUDEDIRS
    include
)

set(
    COMPONENT_REQUIRES
    pthread
)


register_component()