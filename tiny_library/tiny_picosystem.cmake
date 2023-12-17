add_library(tiny_picosystem INTERFACE)

pico_generate_pio_header(tiny_picosystem ${CMAKE_CURRENT_LIST_DIR}/screen.pio)
pico_generate_pio_header(tiny_picosystem ${CMAKE_CURRENT_LIST_DIR}/screen_double.pio)

target_sources(tiny_picosystem INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/tiny_picosystem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/hardware.cpp
  ${CMAKE_CURRENT_LIST_DIR}/draw.cpp
  ${CMAKE_CURRENT_LIST_DIR}/utility.cpp
)

set(TINY_PICOSYSTEM_LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/memmap_picosystem.ld)

target_include_directories(tiny_picosystem INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(tiny_picosystem INTERFACE pico_stdlib hardware_pio hardware_spi hardware_pwm hardware_dma hardware_irq hardware_adc hardware_interp)

function(tiny_picosystem_executable NAME SOURCES)
  add_executable(
    ${NAME}
    ${SOURCES}
    ${ARGN}
  )

  # Pull in pico libraries that we need
  target_link_libraries(${NAME} tiny_picosystem)

  # create map/bin/hex file etc.
  pico_add_extra_outputs(${NAME})

  pico_set_linker_script(${NAME} ${TINY_PICOSYSTEM_LINKER_SCRIPT})

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2 DESTINATION .)
endfunction()

function(pixel_double NAME)
  target_compile_options(${NAME} PRIVATE -DPIXEL_DOUBLE)
endfunction()

function(no_overclock NAME)
  target_compile_options(${NAME} PRIVATE -DNO_OVERCLOCK)
endfunction()
