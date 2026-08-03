include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(CeriumTests
    debug/logging/LoggerTests.cpp
    debug/logging/LoggerFilePoolTests.cpp
)

target_link_libraries(CeriumTests
    PRIVATE
        gtest_main
        Cerium
)
