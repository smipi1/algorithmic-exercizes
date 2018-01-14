set(NAME "algorithm")
set(unittest ${NAME}.unittest) 

include_directories(
    ${GTEST_INC_DIR}
)

set(MOCKED_FUNCTIONS
)

add_unittest(
    ${unittest}

    ${unittest}.cpp
)

target_link_libraries(
    ${unittest}

    lib${NAME}

    -pthread
    -lgtest
    -lgmock_main
)
