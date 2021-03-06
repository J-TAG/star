#ifndef STAR_HPP
#define STAR_HPP

/*
 * Logging macroes:
 qDebug() is used for writing custom debug output.
 qInfo() is used for informational messages.
 qWarning() is used to report warnings and recoverable errors in your application.
 qCritical() is used for writing critical error messages and reporting system errors.
 qFatal() is used for writing fatal error messages shortly before exiting.
*/

// Uncomment following macroes to disable output of qDebug(), qInfo() or qWarning()
//#define QT_NO_DEBUG_OUTPUT
//#define QT_NO_INFO_OUTPUT
//#define QT_NO_WARNING_OUTPUT

// Ignore SSL errors [Only for developemnt porpuses]
//#define IGNORE_SSL_ERRORS

#include <QObject>
#include <QDebug>
#include <QPointer>

// Star modules
#include "includes/star/date/CJalaliDate.hpp" // Jalali date handler class
#include "includes/star/web/auth/OAuth2.hpp" // OAuth2 login handler class
#include "includes/star/web/WebAccessManager.hpp" // Web access manager class
#include "includes/star/web/url/UrlManager.hpp" // URL manager class
#include "includes/star/web/auth/ApiToken.hpp" // API Token data model
#include "includes/star/settings/SettingsManager.hpp" // Settings manager class
#include "includes/star/ui/home/UserDetails.hpp" // User details UI class
#include "includes/star/ui/general/Alerts.hpp" // UI Alerts derived from C++ side
#include "includes/star/ui/setup/SetupWizard.hpp" // Setup wizrad handler class
#include "includes/star/date/HijriDateCalculator.hpp" // Hijri date handler class
#include "includes/star/date/events/TodayEvents.hpp" // Today events handler class
#include "includes/star/ui/tasks/TodayTasks.hpp" // Today tasks handler class
#include "includes/star/web/update/UpdateManager.hpp" // Update manager class

namespace star {

class Star : public QObject
{
    Q_OBJECT
public:
    explicit Star(QObject *parent = nullptr);
    ~Star();

    void setJalaliDate(date::CJalaliDate *jalaliDate);
    date::CJalaliDate *getJalaliDate() const;
    void setOAuth2(web::auth::OAuth2 *oAuth2);
    web::auth::OAuth2 *getOAuth2() const;
    void setWebAccessManager(web::WebAccessManager *webAccessManager);
    web::WebAccessManager *getWebAccessManager() const;
    void setUrlManager(web::url::UrlManager *urlManager);
    web::url::UrlManager *getUrlManager() const;
    void setSettingsManager(settings::SettingsManager *settingsManager);
    settings::SettingsManager *getSettingsManager() const;
    void setApiToken(web::auth::ApiToken *apiToken);
    web::auth::ApiToken *getApiToken() const;
    void setUiUserDetails(ui::home::UserDetails *userDetails);
    ui::home::UserDetails *getUiUserDetails() const;
    void setUiAlerts(ui::general::Alerts *alerts);
    ui::general::Alerts *getUiAlerts() const;
    void setUiSetupWizard(ui::setup::SetupWizard *setupWizard);
    ui::setup::SetupWizard *getUiSetupWizard() const;
    void setHijriDate(date::HijriDateCalculator *hijriDate);
    date::HijriDateCalculator *getHijriDate() const;
    void setTodayEvents(date::events::TodayEvents *todayEvents);
    date::events::TodayEvents *getTodayEvents() const;
    void setTodayTasks(ui::tasks::TodayTasks *todayTasks);
    ui::tasks::TodayTasks *getTodayTasks() const;
    void setUpdateManager(web::update::UpdateManager *updateManager);
    web::update::UpdateManager *getUpdateManager() const;


signals:

public slots:
    void start();
    void initObjects();
    void end();
    QString getAppVersion() const;
    int getAppVersionNumber();
    void startTrayApp();

protected:
    QPointer<date::CJalaliDate> pJalaliDate;
    QPointer<web::auth::OAuth2> pOAuth2;
    QPointer<web::WebAccessManager> pWebAccessManager;
    QPointer<web::url::UrlManager> pUrlManager;
    QPointer<settings::SettingsManager> pSettingsManager;
    QPointer<web::auth::ApiToken> pApiToken;
    QPointer<ui::home::UserDetails> pUiUserDetails;
    QPointer<ui::general::Alerts> pUiAlerts;
    QPointer<ui::setup::SetupWizard> pUiSetupWizard;
    QPointer<date::HijriDateCalculator> pHijriDate;
    QPointer<date::events::TodayEvents> pTodayEvents;
    QPointer<ui::tasks::TodayTasks> pTodayTasks;
    QPointer<web::update::UpdateManager> pUpdateManager;
};

}


// Main app object
extern star::Star s;

#endif // STAR_HPP
