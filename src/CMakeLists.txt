add_executable(CeriumApp)

target_sources(CeriumApp
    PRIVATE
        main.cpp
        cerium/debug/logging/LogLevel.cpp
        cerium/debug/logging/Logger.cpp
        cerium/debug/logging/LoggerMiddleware.cpp
        cerium/debug/logging/ConsoleLoggerMiddleware.cpp
        cerium/debug/logging/FileLoggerMiddleware.cpp
        cerium/debug/logging/LoggerFilePool.cpp
        cerium/debug/logging/Logging.cpp
        cerium/project/application.cpp
        cerium/project/project.cpp
        cerium/time/Clock.cpp
)

target_include_directories(CeriumApp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/cerium
)

if(MSVC)
    target_compile_options(CeriumApp PRIVATE
        /W4
        /WX
    )
else()
  target_compile_options(CeriumApp PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
    )
endif()
