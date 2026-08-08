add_library(Cerium)

target_sources(Cerium
    PRIVATE
        cerium/debug/logging/LogLevel.cpp
        cerium/debug/logging/Logger.cpp
        cerium/debug/logging/LoggerMiddleware.cpp
        cerium/debug/logging/ConsoleLoggerMiddleware.cpp
        cerium/debug/logging/FileLoggerMiddleware.cpp
        cerium/debug/logging/LoggerFilePool.cpp
        cerium/debug/logging/Logging.cpp
        application.cpp
        cerium/project/project.cpp
        cerium/time/Clock.cpp
        cerium/document/text.cpp
        cerium/document/TextHistory.cpp
)

target_include_directories(Cerium
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/cerium
)

add_executable(CeriumApp
    main.cpp
)

target_link_libraries(CeriumApp
    PRIVATE
        Cerium
)

if(MSVC)
    target_compile_options(Cerium PRIVATE
        /W4
        /WX
    )
else()
    target_compile_options(Cerium PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
    )
endif()
