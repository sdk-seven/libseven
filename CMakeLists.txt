#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    # Default to MinSizeRel build type
    set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

project(libseven C ASM)
set(CMAKE_INCLUDE_FLAG_ASM "-Wa,-I")

add_library(seven STATIC
    src/bios.c
    src/bios.s
    src/dma.s
    src/input.c
    src/irq.c
    src/irq_entry.s
    src/sram.s
    src/timer.c
    src/video/oam.s
    src/video/vram.c
)

target_include_directories(seven PUBLIC include/)
target_include_directories(seven PRIVATE src/)

target_compile_options(seven PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-O2 -g3 -gdwarf-4 -ffunction-sections -fdata-sections -std=c99 -Wall -Wextra -Wpedantic -mabi=aapcs -mcpu=arm7tdmi -mthumb -masm-syntax-unified>
)

# Allow the string "libseven" as a parameter for target_link_libraries
add_library(libseven ALIAS seven)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT AND EXISTS $ENV{DEVKITPRO})
    file(TO_CMAKE_PATH "$ENV{DEVKITPRO}" ENV_DEVKITPRO)
    set(CMAKE_INSTALL_PREFIX "${ENV_DEVKITPRO}/libseven" CACHE PATH "..." FORCE)
endif()

install(TARGETS seven LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
