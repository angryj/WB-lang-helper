cmake_minimum_required(VERSION 3.10)
project(WB-lang-helper VERSION 0.1.0 LANGUAGES C CXX)

add_executable(WB-lang-helper)

target_sources(WB-lang-helper
    PRIVATE
        main.cpp
        ShittyStack.cpp
)