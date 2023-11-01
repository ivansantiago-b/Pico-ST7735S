add_library(st7735s INTERFACE)

target_sources(st7735s INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/st7735s.c
    )

target_include_directories(st7735s INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(st7735s INTERFACE hardware_gpio hardware_spi pico_time)