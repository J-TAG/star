#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlContext>
#include <QFont>

// C++ Modules
#include "includes/star/Star.hpp"

int main(int argc, char *argv[])
{
    // Organization details
    QCoreApplication::setOrganizationName("PureSoft");
    QCoreApplication::setOrganizationDomain("puresoftware.org");
    QCoreApplication::setApplicationName("Star");

    QApplication app(argc, argv);

    // Set application font
    QFont tFont;
    tFont.setFamily("IRANSans");
    app.setFont(tFont);

    // Make QML engine
    QQmlApplicationEngine engine;

#ifdef IGNORE_SSL_ERRORS
    // Ignore SSL Errors
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    QSslConfiguration::setDefaultConfiguration(sslConf);
#endif

    // Load C++ side, modules

    // Initialize application objects
    s.initObjects();

    // Star main object
    engine.rootContext()->setContextProperty("star", &s);

    // Jalali date handler
    engine.rootContext()->setContextProperty("jalaliDate", s.getJalaliDate());

    // OAuth2 handler
    engine.rootContext()->setContextProperty("oauth2", s.getOAuth2());

    // User details UI class
    engine.rootContext()->setContextProperty("userDetails", s.getUiUserDetails());

    // Alerts UI class
    engine.rootContext()->setContextProperty("alerts", s.getUiAlerts());

    // Settings manager class
    engine.rootContext()->setContextProperty("settings", s.getSettingsManager());

    // Setup wizard class
    engine.rootContext()->setContextProperty("setup", s.getUiSetupWizard());

    // Hijri date handler
    engine.rootContext()->setContextProperty("hijriDate", s.getHijriDate());

    // Today events handler
    engine.rootContext()->setContextProperty("todayEvents", s.getTodayEvents());

    // Today tasks handler
    engine.rootContext()->setContextProperty("todayTasks", s.getTodayTasks());

    // Update manager
    engine.rootContext()->setContextProperty("updater", s.getUpdateManager());

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
