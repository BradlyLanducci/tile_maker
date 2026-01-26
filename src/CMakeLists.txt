include(FetchContent)

FetchContent_Declare(
        JUCE
        GIT_REPOSITORY "git@github.com:juce-framework/JUCE.git"
        GIT_TAG "master"
        SOURCE_DIR ${CMAKE_BINARY_DIR}/JUCE
        BINARY_DIR ${CMAKE_BINARY_DIR}/JUCE_build
)
FetchContent_MakeAvailable(JUCE)

juce_add_gui_app(${PROJECT_NAME} PRODUCT_NAME "Iso Tile Maker")
juce_generate_juce_header(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
                ${CMAKE_SOURCE_DIR}/src
)

target_compile_definitions(${PROJECT_NAME} 
        PRIVATE
                JUCE_WEB_BROWSER=0
                JUCE_USE_CURL=0
                JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PROJECT_NAME>"
                JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")

target_link_libraries(${PROJECT_NAME} 
        PRIVATE
                juce::juce_recommended_config_flags
                juce::juce_recommended_lto_flags
                juce::juce_recommended_warning_flags
                juce::juce_gui_extra)
