include(FetchContent)

FetchContent_Declare(
        JUCE
        GIT_REPOSITORY "git@github.com:juce-framework/JUCE.git"
        GIT_TAG "master"
        SOURCE_DIR ${CMAKE_BINARY_DIR}/JUCE
        BINARY_DIR ${CMAKE_BINARY_DIR}/JUCE_build
)
FetchContent_MakeAvailable(JUCE)

FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY "https://github.com/Neargye/magic_enum.git"
        GIT_TAG "master"
        SOURCE_DIR "${CMAKE_BINARY_DIR}/magic_enum"
        BINARY_DIR "${CMAKE_BINARY_DIR}/magic_enum_build"
)
FetchContent_MakeAvailable(magic_enum)

juce_add_binary_data(
    Assets 
    SOURCES
        ${CMAKE_SOURCE_DIR}/assets/nine_slice_panel.png
        ${CMAKE_SOURCE_DIR}/assets/m5x7.ttf
)

set_target_properties(Assets PROPERTIES FOLDER "Targets")

juce_add_gui_app(${PROJECT_NAME} PRODUCT_NAME "Iso Tile Maker")
juce_generate_juce_header(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

target_sources(${PROJECT_NAME} 
        PRIVATE 
                ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
                ${CMAKE_SOURCE_DIR}/src
                ${CMAKE_SOURCE_DIR}/dependencies
)

target_compile_definitions(${PROJECT_NAME} 
        PRIVATE
                JUCE_WEB_BROWSER=0
                JUCE_USE_CURL=0
                JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PROJECT_NAME>"
                JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>"
)

target_link_libraries(${PROJECT_NAME} 
        PRIVATE
                Assets
                juce::juce_recommended_config_flags
                juce::juce_recommended_lto_flags
                juce::juce_recommended_warning_flags
                juce::juce_gui_extra
                magic_enum
)
