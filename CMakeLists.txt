# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

cmake_minimum_required(VERSION 3.13)

# Set project standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Pull in Raspberry Pi Pico SDK (must be before project definition)
include(pico_sdk_import.cmake)

# Project name and supported languages
project(team_45 C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Specify the Pico board type
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Add the executable
add_executable(team_45
    team_45.c            # Main file           
    gy87.c               # MPU6050 driver file
    IR.c                 # IR sensor driver file
    dht11.c              # DHT11 driver file
    hardware_control.c   # Hardware (PWM, LED, Motor, etc.) control file
)

# Set the program name and version
pico_set_program_name(team_45 "team_45")
pico_set_program_version(team_45 "0.1")

# Configure standard I/O
pico_enable_stdio_uart(team_45 0) # Disable UART output
pico_enable_stdio_usb(team_45 1) # Enable USB output

# Link required libraries
target_link_libraries(team_45
    pico_stdlib          # Standard library
    hardware_i2c         # I2C library for sensors
    hardware_pwm         # PWM control
    pico_cyw43_arch_none # Wi-Fi support (optional, no threading)
)

# Include project header directories
target_include_directories(team_45 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR} # Include all header files in the project directory
)

# Add extra outputs (e.g., UF2, binary, hex)
pico_add_extra_outputs(team_45)
