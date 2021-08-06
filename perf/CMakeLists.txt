project(PerformanceTesting)
add_subdirectory(gbench)
include_directories(${CMAKE_SOURCE_DIR}/external ${CMAKE_SOURCE_DIR}/include)

# adding the Google_Tests_run target
add_executable(PerformanceTesting perf.cpp)
target_link_libraries(PerformanceTesting benchmark::benchmark)

target_compile_options(PerformanceTesting PUBLIC --std=c++17)