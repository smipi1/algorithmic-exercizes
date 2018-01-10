include (CTest)
include(${CMAKE_CURRENT_LIST_DIR}/conditionally-execute-unittest.cmake)

macro (add_unittest NAME SOURCE)

    add_executable(
        ${NAME}

        ${SOURCE}
        ${ARGN}
    )

    string(REPLACE ";" ",--wrap=" ${NAME}.linker-wrap-args
        "-Wl;${MOCKED_FUNCTIONS}"
    )

    set_target_properties(
        ${NAME}
        PROPERTIES

        LINK_FLAGS "${LD_FLAGS_STR} ${${NAME}.linker-wrap-args}"
    )

    conditionally_execute_unittest(
        ${NAME}
    )
    
    add_test (NAME ${NAME} COMMAND ${NAME})

endmacro (add_unittest)
