cmake_minimum_required(VERSION 3.13)
# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
project(picoemp)
 
pico_sdk_init()

add_executable(picoemp)


target_sources(picoemp PRIVATE
        main.c
        picoemp.c
        )

target_link_libraries(picoemp PRIVATE pico_stdlib hardware_pwm)
pico_add_extra_outputs(picoemp)

# enable usb output, disable uart output
pico_enable_stdio_usb(picoemp 1)
pico_enable_stdio_uart(picoemp 0)
