cmake_minimum_required(VERSION 3.1)
project(cplusplus-concurrent)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(3rdparty/spdlog/include)

option(BUILD_UNIT_TESTS "Enable unit test" ON)

if (BUILD_UNIT_TESTS)
    enable_testing()
    add_subdirectory(test/src)
endif ()

set(header_files
        include/BoundedBlockingQueue.h
        include/Utils.h
        include/Runnable.h
        include/Logger.h
        include/ThreadPoolExecutor.h
        )
set(source_files
        src/BoundedBlockingQueue.cc
        src/Utils.cc
        src/Runnable.cc
        src/Logger.cc
        src/ThreadPoolExecutor.cc
        )

add_library(cplusplus-concurrent STATIC
        ${header_files}
        ${source_files}
        )

set_target_properties(cplusplus-concurrent
        PROPERTIES
        LINKER_LANGUAGE CXX
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        OUTPUT_NAME cplusplus-concurrent
        )