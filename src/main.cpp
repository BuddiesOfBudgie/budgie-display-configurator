// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#include <KAboutData>
#include <KColorSchemeManager>
#include <KLocalizedQmlContext>
#include <KLocalizedString>
#include <QApplication>
#include <QIcon>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "libdisplayconfig/backend.hpp"
#include "libdisplayconfig/types.hpp"
#include <QDBusMetaType>

int main(int argc, char* argv[]) {
  // Register D-Bus meta types
  qDBusRegisterMetaType<bd::Outputs::OutputModeInfo>();
  qDBusRegisterMetaType<bd::Outputs::OutputModesMap>();
  qSetMessagePattern(QStringLiteral("[%{type}] %{if-debug}[%{file}:%{line} %{function}]%{endif}%{message}"));

  // Hardcoded (can be overridden using QT_LOGGING_RULES) so we can have a bunch of logging
  // But then filter out noise from QML / scenegraph
  QLoggingCategory::defaultCategory()->setEnabled(QtMsgType::QtDebugMsg, true);
  QLoggingCategory::defaultCategory()->setEnabled(QtMsgType::QtInfoMsg, true);
  QLoggingCategory::defaultCategory()->setEnabled(QtMsgType::QtWarningMsg, true);
  QLoggingCategory::defaultCategory()->setEnabled(QtMsgType::QtCriticalMsg, true);
  QLoggingCategory::defaultCategory()->setEnabled(QtMsgType::QtFatalMsg, true);
  QLoggingCategory::defaultCategory()->setFilterRules(QStringLiteral("*.debug=true"));
  QLoggingCategory::defaultCategory()->setFilterRules(QStringLiteral("qt.scenegraph.general=false"));

  // KIconTheme::initTheme();
  KLocalizedString::setApplicationDomain("budgie-display-configurator");

  QApplication::setOrganizationName(QStringLiteral("Buddies of Budgie"));
  QApplication::setOrganizationDomain(QStringLiteral("buddiesofbudgie.org"));

  QGuiApplication::setDesktopFileName(QStringLiteral("org.buddiesofbudgie.DisplayConfig"));

  QApplication app(argc, argv);
  QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-display")));

  if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) { QQuickStyle::setStyle(QStringLiteral("org.kde.desktop")); }

  // #region Set up about data

  // Do explicit calls instead of constructing with all args
  // Makes it clearer what arg maps to what param
  KAboutData aboutData;
  aboutData.setComponentName(QStringLiteral("budgie-display-configurator"));
  aboutData.setVersion("0.1.0");
  aboutData.setShortDescription(i18n("Display configurator for Budgie Desktop"));
  aboutData.setLicense(KAboutLicense::MPL_V2);
  aboutData.setCopyrightStatement(QStringLiteral("(c) 2025 Buddies of Budgie"));

  aboutData.setHomepage(QStringLiteral("https://buddiesofbudgie.org"));
  aboutData.setBugAddress("https://forge.moderndesktop.dev/BuddiesOfBudgie/budgie-display-configurator");

  aboutData.addAuthor(QStringLiteral("Joshua Strobl"), i18n("Maintainer"), QStringLiteral("me@joshuastrobl.com"), QStringLiteral("https://joshuastrobl.com"));

  KAboutData::setApplicationData(aboutData);

  qmlRegisterSingletonType("org.buddiesofbudgie.DisplayConfig", 1, 0, "About", [](QQmlEngine* engine, QJSEngine*) -> QJSValue {
    return engine->toScriptValue(KAboutData::applicationData());
  });

  // #endregion

  // #region Set up backend

  Backend backend;
  qmlRegisterSingletonInstance("org.buddiesofbudgie.DisplayConfig", 1, 0, "Backend", &backend);

  // #endregion

  // KColorSchemeManager::instance();

  QQmlApplicationEngine engine;
  auto                  ctx = new KLocalizedQmlContext(&engine);
  engine.rootContext()->setContextObject(ctx);
  QQmlEngine::setContextForObject(ctx, engine.rootContext());
  engine.loadFromModule("org.buddiesofbudgie.DisplayConfig", "Main");

  if (engine.rootObjects().isEmpty()) { return EXIT_FAILURE; }

  return app.exec();
}
