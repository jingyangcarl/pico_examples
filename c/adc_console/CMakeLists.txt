cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(adc_console)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

if (TARGET tinyusb_device)

    # rest of your project
    add_executable(adc_console adc_console.c)

    # pull in common dependencies
    target_link_libraries(adc_console pico_stdlib hardware_adc)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(adc_console)

    # enable printf output via USB CDC (USB serial)
    pico_enable_stdio_usb(adc_console 1)

    # disable printf output via uart
    pico_enable_stdio_uart(adc_console 0)

    # add url via pico_set_program_url
    # pico_set_program_url(adc_console)

elseif (PICO_ON_DEVICE)
    message(WARNING "not building adc_console becuase TinyUSB submodule is not initialized in the SDK")

endif()