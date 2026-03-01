# Fetch GoogleTest from GitHub
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
if(MSVC)
  if(DEFINED MSVC_RUNTIME AND MSVC_RUNTIME STREQUAL "dynamic")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  else()
    set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
  endif()
endif()

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

project (PlateTectonicsTests)

# Build tests list. Regression PNG test is added only when PNG is available.
set(PLATE_TEST_SOURCES
  test_acceptance.cpp
  test_heightmap.cpp
  test_plate.cpp
  test_rectangle.cpp
  test_sqrdmd.cpp
  test_randomness.cpp
  test_portability.cpp
  test_bounds.cpp
  test_mass.cpp
  test_movement.cpp
)

# Find PNG for regression test artifacts (optional)
set(CMAKE_FIND_FRAMEWORK LAST)
find_package(PNG QUIET)
if(PNG_FOUND)
  list(APPEND PLATE_TEST_SOURCES
    test_regression.cpp
    ../examples/map_drawing.cpp
  )
else()
  message(STATUS "PNG/ZLIB not found: skipping test_regression.cpp")
endif()

add_executable(PlateTectonicsTests ${PLATE_TEST_SOURCES})

add_test(NAME PlateTectonicsTests COMMAND PlateTectonicsTests)
# Set working directory for tests to the build root so PNG artifacts are written to a known location
set_tests_properties(PlateTectonicsTests PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

target_include_directories(PlateTectonicsTests PRIVATE ../src ../examples)
if(PNG_FOUND)
  target_include_directories(PlateTectonicsTests PRIVATE ${PNG_INCLUDE_DIRS})
endif()

# Standard linking to gtest stuff.
target_link_libraries(PlateTectonicsTests PRIVATE gtest gtest_main)

# Extra linking for the project.
target_link_libraries(PlateTectonicsTests PRIVATE PlateTectonics)
if(PNG_FOUND)
  target_link_libraries(PlateTectonicsTests PRIVATE PNG::PNG)
endif()


