# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(IoT_Sulari)

zephyr_include_directories(include)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/sensors.c)
target_sources(app PRIVATE src/buttons.c)
target_sources(app PRIVATE src/lte.c)
target_sources(app PRIVATE src/mqtt_connection.c)
target_sources(app PRIVATE src/sms_wrapper.c)