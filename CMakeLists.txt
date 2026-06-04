cmake_minimum_required(VERSION 3.11)

project(TestHelperPlugin LANGUAGES CXX)

add_compile_options(/W3)

file(GLOB SRC_LIST *.cpp *.h)

add_library(TestHelperPlugin SHARED ${SRC_LIST})

target_compile_definitions(TestHelperPlugin 
    PRIVATE
        WIN32
        NDEBUG
        _WINDOWS
        _USRDLL
        UNICODE
        _UNICODE
        TESTHELPERPLUGIN_EXPORTS
)