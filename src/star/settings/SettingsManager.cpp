#include <QJsonDocument>
#include <QJsonObject>
#include <functional>
#include "includes/star/Star.hpp"


star::settings::SettingsManager::SettingsManager() {}

star::settings::SettingsManager::~SettingsManager() {}

void star::settings::SettingsManager::setLocalSettings(QNetworkReply *reply)
{
    // Read data
    auto jsoc = QJsonDocument::fromJson(reply->readAll());
    auto json = jsoc.object();

    // Name
    auto name = json["user"].toObject()["name"].toString();
    s.getUiUserDetails()->updateName(name.isNull() ? "[نام شما]" : name);

    // Birthday
    auto birthday = QDateTime::fromSecsSinceEpoch(json["user"].toObject()["birthday"].toInt());
    s.getUiUserDetails()->updateBirthday(birthday);

    // Show birth time in second, etc.
    auto showBirthVariants = json["user"].toObject()["showBirthVariants"].toBool();
    s.getUiUserDetails()->updateShowBirthVariants(showBirthVariants);

    // Celebrate birthday
    auto celebrateBirthday = json["user"].toObject()["celebrateBirthday"].toBool();
    s.getUiUserDetails()->updateCelebrateBirthday(celebrateBirthday);

    // Auto start
    auto autoStart = json["app"].toObject()["windows"].toObject()["autoStart"].toBool();
    s.getUiUserDetails()->updateAutoStart(autoStart);
}

void star::settings::SettingsManager::setOnlineValue(const QString &strJson)
{
    auto successFunctor = std::bind( &SettingsManager::successOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    auto failFunctor = std::bind( &SettingsManager::failedOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    s.getWebAccessManager()->withAuthenticationHeader()->post(
                s.getUrlManager()->getPureUrl("apps/fa/star-v4/settings/set.html"),
                strJson, successFunctor, failFunctor);
}

void star::settings::SettingsManager::getOnlineSettings()
{
    auto successFunctor = std::bind( &star::settings::SettingsManager::successOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    auto failFunctor = std::bind( &star::settings::SettingsManager::failedOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    s.getWebAccessManager()->withAuthenticationHeader()->get(
                s.getUrlManager()->getPureUrl("apps/fa/star-v4/settings/get.html"),
                successFunctor, failFunctor);
}

void star::settings::SettingsManager::setValue(const QString &strKey, const QVariant &value)
{
    this->_settings.setValue(strKey, value);
}

QString star::settings::SettingsManager::getStringValue(const QString &strKey, const QString &strDefaultValue) const
{
    return this->_settings.value(strKey, strDefaultValue).toString();
}

int star::settings::SettingsManager::getIntValue(const QString &strKey, int nDefaultValue)
{
    return this->_settings.value(strKey, nDefaultValue).toInt();
}

void star::settings::SettingsManager::removeValue(const QString &strKey)
{
    return this->_settings.remove(strKey);
}

void star::settings::SettingsManager::failedOnlineSettingsFunctor(QNetworkReply *reply, int httpStatus)
{

    if(httpStatus == 404) {

        // This user has not any settings yet, so show them setup wizard to begin
        emit s.getUiSetupWizard()->initSetupWizard();

        // Close all login related boxes
        emit s.getOAuth2()->showLoginBox(false);

        qWarning() << Q_FUNC_INFO << ": There is no online settings. Showing setup wizard:" <<
                      httpStatus << reply->readAll();

    } else {
        // Online settings failed to retrive, so we can update with false result

        emit this->onlineSettingsUpdated(false, QString());

        qWarning() << Q_FUNC_INFO << ": Getting online settings failed. HTTP status and result:" <<
                      httpStatus << reply->readAll();
    }

}

void star::settings::SettingsManager::successOnlineSettingsFunctor(QNetworkReply *reply, int)
{
    // Online settings retrived successfully, now we can update it in our app

    this->setLocalSettings(reply);

    emit this->onlineSettingsUpdated(true, reply->readAll());
}
