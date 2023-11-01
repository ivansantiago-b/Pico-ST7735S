add_executable(st7735s_test st7735s_test.c)

pico_set_program_name(st7735s_test "st7735s_test")
pico_set_program_version(st7735s_test "0.1")

pico_enable_stdio_uart(st7735s_test 0)
pico_enable_stdio_usb(st7735s_test 1)

# Add the standard library to the build
target_link_libraries(st7735s_test
    pico_stdlib
    )

# Add the standard include files to the build
target_include_directories(st7735s_test PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(st7735s_test 
    st7735s
    )

pico_add_extra_outputs(st7735s_test)