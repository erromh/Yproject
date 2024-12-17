cmake_minimum_required(VERSION 3.8)

project(Yproject VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/lib)

include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG master 
)
FetchContent_MakeAvailable(juce)

juce_add_gui_app(Yproject
    PRODUCT_NAME "Yproject" 
)

target_sources(Yproject PRIVATE
    main.cpp 
    CourseLib.h 
    CourseLib.cpp 
    Process.h
)

target_link_libraries(Yproject PRIVATE
    juce::juce_gui_basics
    juce::juce_gui_extra
)
