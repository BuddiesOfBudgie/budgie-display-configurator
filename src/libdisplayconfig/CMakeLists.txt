# SPDX-FileCopyrightText: Budgie Desktop Developers
#
# SPDX-License-Identifier: MPL-2.0

set(backend_SRCS)

qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.Config.xml ConfigInterface)
qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.Displays.xml OutputsInterface)
qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.Output.xml OutputInterface)
qt_add_dbus_interface(backend_SRCS dbus/schemas/DisplaySchema.OutputMode.xml OutputModeInterface)

add_library(
    libdisplayconfig STATIC
    backend.cpp
    backend.hpp
    enums/connectionstate.hpp
    layout.cpp
    layout.hpp
    models/layoutmodel.cpp
    models/layoutmodel.hpp
    models/outputmodel.cpp
    models/outputmodel.hpp
    output/output.cpp
    output/output.hpp
    ${backend_SRCS}
)

generate_export_header(libdisplayconfig BASE_NAME LibDisplayConfig)

target_include_directories(libdisplayconfig PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/enums ${CMAKE_CURRENT_SOURCE_DIR}/models)

target_link_libraries(libdisplayconfig PRIVATE Qt::Core Qt::DBus Qt::Qml)
