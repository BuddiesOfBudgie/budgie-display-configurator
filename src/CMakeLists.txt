# SPDX-FileCopyrightText: Budgie Desktop Developers
#
# SPDX-License-Identifier: MPL-2.0

add_subdirectory(libdisplayconfig)

ecm_find_qmlmodule(org.kde.kirigami REQUIRED)

add_executable(org.buddiesofbudgie.DisplayConfig)
ecm_add_qml_module(
    org.buddiesofbudgie.DisplayConfig
    URI
    "org.buddiesofbudgie.DisplayConfig"
    GENERATE_PLUGIN_SOURCE
)

target_sources(org.buddiesofbudgie.DisplayConfig
    PRIVATE
    main.cpp
)

ecm_target_qml_sources(org.buddiesofbudgie.DisplayConfig
    SOURCES
    qml/Main.qml
    qml/LayoutManager.qml
)

target_link_libraries(org.buddiesofbudgie.DisplayConfig
    PRIVATE
    Qt6::Core
    Qt6::DBus
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::QuickControls2
    Qt6::Widgets
    KF6::ColorScheme
    KF6::CoreAddons
    KF6::I18n
    KF6::I18nQml
    libdisplayconfig
)
