cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(hello_usb)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

if (TARGET tinyusb_device)

    # rest of your project
    add_executable(hello_usb hello_usb.c)

    # pull in common dependencies
    target_link_libraries(hello_usb pico_stdlib)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hello_usb)

    # enable printf output via USB CDC (USB serial)
    pico_enable_stdio_usb(hello_usb 1)

    # disable printf output via uart
    pico_enable_stdio_uart(hello_usb 0)

    # add url via pico_set_program_url
    # pico_set_program_url(hello_usb)

elseif (PICO_ON_DEVICE)
    message(WARNING "not building hello_usb becuase TinyUSB submodule is not initialized in the SDK")

endif()