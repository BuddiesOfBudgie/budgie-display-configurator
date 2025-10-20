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
    libdisplayconfig STATIC
    backend.cpp
    backend.hpp
    enums/connectionstate.hpp
    layout/LayoutManager.cpp
    layout/LayoutManager.hpp
    layout/LayoutManagerModel.cpp
    layout/LayoutManagerModel.hpp
    output/output.cpp
    output/output.hpp
    output/model.cpp
    output/model.hpp
    ${backend_SRCS}
)

generate_export_header(libdisplayconfig BASE_NAME LibDisplayConfig)

target_include_directories(libdisplayconfig PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(libdisplayconfig PRIVATE Qt::Core Qt::DBus Qt::Qml)
