# SPDX-FileCopyrightText: Budgie Desktop Developers
#
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.20)

project(budgie-display-configurator VERSION 0.0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

install(TARGETS org.buddiesofbudgie.DisplayConfig ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES
                         FATAL_ON_MISSING_REQUIRED_PACKAGES)
