file(GLOB SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

message(${SOURCES})

add_executable(${PROJECT_NAME}
        ${SOURCES}
        main.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/src
)
