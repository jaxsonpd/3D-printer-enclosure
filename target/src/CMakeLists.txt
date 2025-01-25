add_executable(EnclosureMonitor main.c fan_speed.c circular_buffer.c temp_sensor.c)

target_compile_options(EnclosureMonitor PRIVATE -Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall -Wstrict-prototypes -Wextra)
target_link_libraries(EnclosureMonitor PRIVATE avr-extends)
target_link_libraries(EnclosureMonitor PRIVATE custom-can-protocol)

add_program_target(EnclosureMonitor PROGRAM_TARGET program)