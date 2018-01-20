cmake_minimum_required (VERSION 2.8.9)

set(NAME algorithm)

project (${NAME})

link_directories(
    ${CMAKE_PREFIX_PATH}/lib
)

include_directories(
    ${CMAKE_PREFIX_PATH}/include
    ${CMAKE_PREFIX_PATH}/usr/include
    include
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -ggdb -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -ggdb -std=c++11")

set(CMAKE_C_FLAGS_DEBUG
    "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -O0 -fPIC"
)

set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -O0 -fPIC"
)

set(CMAKE_LD_FLAGS_DEBUG
    "${CMAKE_LD_FLAGS_DEBUG} -lgcov -fprofile-arcs -ftest-coverage -O0 -fPIC"
)

set(CMAKE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include/cmake)

set(MOCKS_DIR ${TEST_DIR}/mocks)
include(${CMAKE_INCLUDE_DIR}/gtest-unittest.cmake)

include(CheckTypeSize)
check_type_size("off_t" SIZEOF_OFF_T)

if(SIZEOF_OFF_T GREATER 7)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64")
endif()

if("$ENV{PKG_TYPE}" STREQUAL "library")

    add_subdirectory(test)

    add_library(
        lib${NAME}
    
        src/${NAME}.cpp
    )
    
    install(
        TARGETS
            lib${NAME}
        DESTINATION
            lib
    )

elseif("$ENV{PKG_TYPE}" STREQUAL "executable")

    add_executable(
        ${NAME}
    
        src/${NAME}.cpp
    )
    
    install(
        TARGETS
            ${NAME}
        DESTINATION
            bin
    )

else()

    message(FATAL_ERROR "PKG_TYPE not in (executable|library)")

endif()