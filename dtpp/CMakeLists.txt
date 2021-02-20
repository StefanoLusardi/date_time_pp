set(PROJECT_NAME dtpp)

set(CONAN_SYSTEM_INCLUDES ON)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt NO_OUTPUT_DIRS BASIC_SETUP KEEP_RPATHS BUILD missing)

add_library(${PROJECT_NAME} SHARED
    src/date_t.cpp
    src/time_t.cpp
    src/datetime_t.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE LIB_DTPP)

target_include_directories(${PROJECT_NAME}
    PRIVATE include/${PROJECT_NAME}
    PUBLIC include
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})

if(${DTPP_ENABLE_ASAN} OR ${DTPP_ENABLE_LSAN} OR ${DTPP_ENABLE_MSAN})
    if(NOT WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        
        # Address Sanitizer: already includes support for Leak Sanitizer
        if(${DTPP_ENABLE_ASAN}) 
            message(STATUS "::dtpp:: Address Sanitizer enabled")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -g -fno-omit-frame-pointer -fsanitize=address")
            set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
        endif()

        # Leak Sanitizer: set only if Address Sanitizer is not enabled.
        if(${DTPP_ENABLE_LSAN} AND NOT ${DTPP_ENABLE_ASAN})
            message(STATUS "::dtpp:: Leak Sanitizer enabled")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-omit-frame-pointer -fsanitize=leak")
            set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=leak")
        endif()

        # Memory Sanitizer
        if(${DTPP_ENABLE_MSAN})
            message(STATUS "::dtpp:: Memory Sanitizer enabled")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -g -fno-omit-frame-pointer -fsanitize=memory -fPIE -pie")
            set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=memory -fPIE -pie")
        endif()	

    else()    
		message(ERROR "Sanitizers not supported on the current platform")
	endif()
endif()

if(${DTPP_ENABLE_CODE_COVERAGE})
	if(NOT WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
		message(STATUS "::dtpp:: Code coverage enabled")
		target_compile_options(dtpp INTERFACE --coverage -O0 -g -fno-inline -fno-inline-small-functions -fno-default-inline -fkeep-inline-functions)
		target_link_options(dtpp INTERFACE --coverage -fno-inline -fno-inline-small-functions -fno-default-inline -fkeep-inline-functions)
    else()
		message(ERROR "Coverage not supported on the current platform")
	endif()
endif()  