project(UnitTest)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/external ${CMAKE_SOURCE_DIR}/include)

find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})


# adding the Google_Tests_run target
add_executable(UnitTest test_hilbert.cpp test_math.cpp test_string_helper.cpp test_cartesian.cpp test_sys.cpp
        test_constant.cpp test_binary.cpp test_base64.cpp test_integration.cpp test_randxor.cpp)
target_link_libraries(UnitTest gtest gtest_main gmock MPI::MPI_CXX)
target_compile_options(UnitTest PUBLIC --std=c++17)




