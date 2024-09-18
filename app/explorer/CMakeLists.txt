#-------------------------------------------------------------------------------
# Zephyr Example Application
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/) # new add, set BOARD_ROOT.

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

target_sources(app PRIVATE src/main.c)

FILE(GLOB app_sources src/*.c)


target_sources(app PRIVATE
		src/modules/util_module.c
		src/modules/modules_common.c
        src/modules/flash_module.c
        src/modules/socket_can_module.c
)

target_sources(app PRIVATE
		src/events/util_module_event.c
)

# target_sources(app PRIVATE
# )

zephyr_library_include_directories(src/modules)
zephyr_library_include_directories(src/Algorithm)
zephyr_library_include_directories(src/events)

zephyr_library_include_directories(${ZEPHYR_BASE}/drivers/flash)

add_subdirectory_ifdef(CONFIG_WATCHDOG_APPLICATION src/watchdog)

# exec_program(
#     "git"
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ARGS "log -1 --format=%H "
#     OUTPUT_VARIABLE VERSION_HASH )

# add_definitions( -DGIT_HASH="${VERSION_HASH}" )

find_package(Git)
# 生成版本描述字符串类似 TAG-X-gHASH
execute_process(COMMAND ${GIT_EXECUTABLE} describe --abbrev=6 --dirty --always --tags
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE  GIT_REPO_VERSION 
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# 获取最新 commit 日期，YYYY-MM-DD
execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=short
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE  GIT_REPO_DATE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# 获取最新 commit Hash
execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%H
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE  GIT_REPO_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# 写入头文件宏定义的版本字符串，日期和 Hash
file(WRITE ${PROJECT_BINARY_DIR}/repo_version.h
    "#define REPO_VERSION \"${GIT_REPO_VERSION}\"\n#define REPO_DATE \"${GIT_REPO_DATE}\"\n#define REPO_HASH \"${GIT_REPO_HASH}\"\n"
)
# 包含引用目录，源文件可以直接用 #include "repo_version.h" 包含
include_directories(${PROJECT_BINARY_DIR})

aux_source_directory(. SRC)
# 添加头文件依赖，保证更改后重新编译
# add_executable(app ${SRC} ${PROJECT_BINARY_DIR}/repo_version.h)