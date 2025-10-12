# Copyright (c) Kasefuchs
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.16)

project(kusai
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(app)
