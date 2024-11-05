cmake_minimum_required(VERSION 3.14)
project("triangles")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    GEOMETRY_FILES
    src/vector3.cpp
    src/common.cpp
    src/triangle.cpp
    src/plane.cpp
    src/segment.cpp
    src/intersections.cpp
)

add_library(geometry STATIC ${GEOMETRY_FILES})
target_include_directories(geometry PUBLIC includes)

add_executable(triangles main.cpp)
target_link_libraries(triangles geometry)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  tests_bin
  tests/vector3_test.cpp
  tests/plane_test.cpp
  tests/segment_test.cpp
  tests/intersections_test.cpp
  tests/triangle_test.cpp
)

target_link_libraries(tests_bin geometry)

target_link_libraries(
  tests_bin
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests_bin)
