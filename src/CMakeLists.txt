# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(SHIELD sh1106_128x64)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(IoT_Sulari)

zephyr_include_directories(include)

add_subdirectory(drivers)

target_sources(app PRIVATE src/main.c)