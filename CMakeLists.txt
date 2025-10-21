# SPDX-FileCopyrightText: Budgie Desktop Developers
#
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.20)

project(budgie-display-configurator VERSION 0.0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

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

find_package(Qt6 ${QT6_MIN_VERSION} NO_MODULE COMPONENTS Core DBus Gui Quick QuickControls2 Widgets)

set_package_properties(
  Qt6 PROPERTIES
  TYPE REQUIRED
  PURPOSE "Basic application components")

find_package(
  KF6 ${KF6_MIN_VERSION}
  COMPONENTS ColorScheme
             CoreAddons
             I18n
             Kirigami
             QQC2DesktopStyle)

set_package_properties(
  KF6 PROPERTIES
  TYPE REQUIRED
  PURPOSE "Basic application components")

set_package_properties(
  KF6Kirigami PROPERTIES
  TYPE REQUIRED
  PURPOSE "Kirigami application UI framework")

# TODO(JoshStrobl): Add ecm_setup_version call for version setting -- uses the incldue of ECMSetupVersion

add_subdirectory(src)

install(TARGETS org.buddiesofbudgie.DisplayConfig ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.buddiesofbudgie.DisplayConfig.desktop DESTINATION ${KDE_INSTALL_APPDIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
