# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(EXTRA_CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toto.conf)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(kconfig_toto)

target_sources(app PRIVATE src/main.c)

add_subdirectory(toto)
