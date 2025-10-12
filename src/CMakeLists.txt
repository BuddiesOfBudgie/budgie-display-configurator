# SPDX-FileCopyrightText: Budgie Desktop Developers
#
# SPDX-License-Identifier: MPL-2.0

set(KDE_COMPILERSETTINGS_LEVEL 6.0)

set(PROJECT_DEP_VERSION "6.1.80")
set(QT_MIN_VERSION "6.8")
set(KF6_MIN_VERSION "6.6.0")

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(FeatureSummary)
include(ECMSetupVersion)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMFindQmlModule)
include(ECMQmlModule)

find_package(Qt6 REQUIRED COMPONENTS Core DBus Gui Quick QuickControls2 Widgets)

find_package(KF6 REQUIRED COMPONENTS Kirigami I18n CoreAddons QQC2DesktopStyle IconThemes ColorScheme)

# TODO(JoshStrobl): Add ecm_setup_version call for version setting -- uses the incldue of ECMSetupVersion

add_subdirectory(backend)

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
    qml/Outputs.qml
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
    KF6::IconThemes
    backend
)

