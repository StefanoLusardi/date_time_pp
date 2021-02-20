cmake_minimum_required (VERSION 3.10 FATAL_ERROR)

project (dtpp
    LANGUAGES CXX 
    VERSION 1.0.0
    DESCRIPTION "DateTime++"
    HOMEPAGE_URL "https://github.com/StefanoLusardi/dtpp"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake)

option(DTPP_ENABLE_CODE_COVERAGE "Enable code coverage" OFF)

option(DTPP_BUILD_TESTS "Build library tests" ON)
option(DTPP_BUILD_EXAMPLES "Build library examples" ON)
option(DTPP_BUILD_DOCS "Build library documentation" OFF)

option(DTPP_INSTALL_LIBRARY "Install library" OFF)
option(DTPP_INSTALL_EXAMPLES "Install examples" OFF)

option(DTPP_ENABLE_ASAN "Run unit tests with Address Sanitizer support" OFF)
option(DTPP_ENABLE_LSAN "Run unit tests with Leak Sanitizer support" OFF)
option(DTPP_ENABLE_MSAN "Run unit tests with Memory Sanitizer support" OFF)

add_subdirectory(dtpp)

if(${DTPP_BUILD_TESTS})
	message(STATUS "::dtpp:: Building tests")
	#include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif()

if(${DTPP_BUILD_EXAMPLES})
	message(STATUS "::dtpp:: Build examples")
	add_subdirectory(examples)
endif()

if(${DTPP_BUILD_DOCS})
	message("::dtpp:: Building docs")
	add_subdirectory(docs)
endif()