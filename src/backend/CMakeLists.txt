# SPDX-FileCopyrightText: Budgie Desktop Developers
#
# SPDX-License-Identifier: MPL-2.0

add_library(
    backend STATIC
    backend.cpp
    backend.hpp
)

target_include_directories(backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(backend PRIVATE Qt::Core)