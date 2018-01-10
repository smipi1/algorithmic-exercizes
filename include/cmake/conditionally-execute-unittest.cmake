set(CONDITIONALLY_EXECUTE_UNITTEST
    ${CMAKE_CURRENT_LIST_DIR}/scripts/conditionally-execute-unittest.sh
)

macro(conditionally_execute_unittest name)

    add_custom_command(TARGET ${name}
        PRE_BUILD
        COMMAND rm -f ${name}.fails
    )
    
    add_custom_command(TARGET ${name}
        POST_BUILD
        COMMAND ${CONDITIONALLY_EXECUTE_UNITTEST} ${name}
    )

endmacro(conditionally_execute_unittest)
