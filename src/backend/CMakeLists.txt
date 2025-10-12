# SPDX-FileCopyrightText: Budgie Desktop Developers
#
# SPDX-License-Identifier: MPL-2.0

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(backend_SRCS)

qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.BatchSystem.xml BatchSystemInterface)
qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.Displays.xml DisplaysInterface)
qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.Output.xml OutputInterface)
qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.OutputMode.xml OutputModeInterface)

add_library(
    backend STATIC
    backend.cpp
    backend.hpp
    enums.hpp
    ${backend_SRCS}
)

target_include_directories(backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(backend PRIVATE Qt::Core Qt::DBus)