#include <KAboutData>
#include <KColorSchemeManager>
#include <KIconTheme>
#include <KLocalizedQmlContext>
#include <KLocalizedString>
#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "backend/backend.hpp"

int main(int argc, char *argv[]) {
    KIconTheme::initTheme();
    QGuiApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("budgie-display-configurator");
    
    QApplication::setOrganizationName(QStringLiteral("Buddies of Budgie"));
    QApplication::setOrganizationDomain(QStringLiteral("buddiesofbudgie.org"));

    QGuiApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop")));
    QGuiApplication::setDesktopFileName(QStringLiteral("org.buddiesofbudgie.DisplayConfig"));

    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }

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

    aboutData.addAuthor(
        QStringLiteral("Joshua Strobl"),
         i18n("Maintainer"),
          QStringLiteral("me@joshuastrobl.com"),
          QStringLiteral("https://joshuastrobl.com")
    );

    KAboutData::setApplicationData(aboutData);

    qmlRegisterSingletonType(
        "org.buddiesofbudgie.DisplayConfig",
        1, 0,
        "About",
        [](QQmlEngine* engine, QJSEngine *) -> QJSValue {
            return engine->toScriptValue(KAboutData::applicationData());
        }
    );

    // #endregion

    // #region Set up backend

    bd::Backend backend;
    qmlRegisterSingletonInstance("org.buddiesofbudgie.DisplayConfig", 1, 0, "Backend", &backend);

    // #endregion

    KColorSchemeManager::instance();

    QQmlApplicationEngine engine;
    auto ctx = new KLocalizedQmlContext(&engine);
    engine.rootContext()->setContextObject(ctx);
    QQmlEngine::setContextForObject(ctx, engine.rootContext());
    engine.loadFromModule("org.buddiesofbudgie.DisplayConfig", "Main");

    if (engine.rootObjects().isEmpty()) {
        return EXIT_FAILURE;
    }


    return app.exec();
}