cmake_minimum_required(VERSION 3.16)
project(ViteCLI VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -pedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    else()
        add_compile_options(-O3)
    endif()
endif()

# Find required packages
find_package(Threads REQUIRED)

# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(vite ${SOURCES})

# Link libraries
target_link_libraries(vite PRIVATE Threads::Threads)

# Enable filesystem library for older compilers
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
    target_link_libraries(vite PRIVATE stdc++fs)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
    target_link_libraries(vite PRIVATE c++fs)
endif()

# Install target
install(TARGETS vite
    RUNTIME DESTINATION bin
    COMPONENT Runtime
)

# CPack configuration for packaging
set(CPACK_PACKAGE_NAME "ViteCLI")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast, modern build tool for web development")
set(CPACK_PACKAGE_VENDOR "ViteCLI Team")
set(CPACK_PACKAGE_CONTACT "contact@vitecli.dev")

include(CPack)

# Add custom target for clean build
add_custom_target(clean-build
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Add custom target for running the application
add_custom_target(run
    COMMAND ./vite --help
    DEPENDS vite
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add custom target for running interactive mode
add_custom_target(run-interactive
    COMMAND ./vite create --interactive
    DEPENDS vite
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
