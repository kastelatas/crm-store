include(FetchContent)

set(COMPONENT_NAME app)

add_library(app STATIC main.cpp)


target_link_libraries(${COMPONENT_NAME}
    common services)