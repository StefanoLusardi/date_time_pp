set(PROJECT_NAME dtpp_tests)

include(DownloadGoogleTest)
include(GoogleTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/date_test.cpp
	src/datetime_test.cpp
	src/time_test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE dtpp gtest)

gtest_discover_tests(${PROJECT_NAME})
