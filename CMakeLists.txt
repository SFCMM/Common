cmake_minimum_required(VERSION 3.16)
project(common)
project(common VERSION "2")

add_subdirectory(UnitTest)
add_subdirectory(perf)

set(CMAKE_CXX_STANDARD 17)

include_directories(external)
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#option(BUILD_DOC "Build documentation" OFF)
## check if Doxygen is installed
#find_package(Doxygen)
#if (DOXYGEN_FOUND)
#    # set input and output files
#    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
#    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
#
#    # request to configure the file
#    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#    message("Doxygen build started")
#
#    # note the option ALL which allows to build the docs together with the application
#    add_custom_target( doc_doxygen ALL
#            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#            COMMENT "Generating API documentation with Doxygen"
#            VERBATIM )
#else (DOXYGEN_FOUND)
#    message("Doxygen need to be installed to generate the doxygen documentation")
#endif (DOXYGEN_FOUND)

