add_executable(mandelbrot_set mandelbrot_set.c)

pico_set_program_name(mandelbrot_set "Mandelbrot set")
pico_set_program_version(mandelbrot_set "0.1")

pico_enable_stdio_uart(mandelbrot_set 0)
pico_enable_stdio_usb(mandelbrot_set 1)

# Add the standard library to the build
target_link_libraries(mandelbrot_set
    pico_stdlib
    )

# Add the standard include files to the build
target_include_directories(mandelbrot_set PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(mandelbrot_set 
    st7735s
    )

pico_add_extra_outputs(mandelbrot_set)