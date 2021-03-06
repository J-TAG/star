#ifndef WEBACCESSMANAGER_HPP
#define WEBACCESSMANAGER_HPP

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QNetworkAccessManager>

namespace star {

namespace web {

class WebAccessManager : public QObject
{
    Q_OBJECT
public:
    WebAccessManager();
    virtual ~WebAccessManager();

    WebAccessManager *withAuthenticationHeader();

    void get(const QString &strUrl, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
             std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor = [](QNetworkReply *, int){});

    void post(const QString &strUrl, const QUrlQuery &queries, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
              std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor,
              const QString &strContentType = QStringLiteral("application/x-www-form-urlencoded"));

    void post(const QString &strUrl, const QString &strBody, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
              std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor = [](QNetworkReply *, int){},
              const QString &strContentType = QStringLiteral("application/json"));

    void put(const QString &strUrl, const QString &strBody, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
            std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor = [](QNetworkReply *, int){},
            const QString &strContentType = QStringLiteral("application/json"));

    void deleteResource(const QString &strUrl, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
           std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor = [](QNetworkReply *, int){});

private:
    QNetworkRequest generateNormalRequest(const QString &strUrl);
    QNetworkRequest &setHeaders(QNetworkRequest &request);


private:
    QPointer<QNetworkAccessManager> pManager;
    QHash<QString, QString> hashHeaders;
};

}

}

#endif // WEBACCESSMANAGER_HPP
