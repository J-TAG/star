#include "includes/star/Star.hpp"

#include <QNetworkReply>
#include <QUrlQuery>


star::web::WebAccessManager::WebAccessManager():pManager(new QNetworkAccessManager(this)) {

}

star::web::WebAccessManager::~WebAccessManager() {}

void star::web::WebAccessManager::get(const QString &strUrl, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
                                      std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor = [](QNetworkReply *, int){})
{
    QNetworkRequest request(this->generateNormalRequest(strUrl));

    QNetworkReply *reply = this->pManager->get(request);

    connect(reply, &QIODevice::readyRead,  [reply, functor, failFunctor]() {

        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(reply->error() == QNetworkReply::NoError && httpStatusCode >= 200 && httpStatusCode < 300) {
            functor(reply, httpStatusCode);
        } else {
            failFunctor(reply, httpStatusCode);
        }

        reply->deleteLater();
    });
}

void star::web::WebAccessManager::post(const QString &strUrl, const QUrlQuery &queries, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
                                       std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor,
                                       const QString &strContentType)
{
    QNetworkRequest request(this->generateNormalRequest(strUrl));

    request.setHeader(QNetworkRequest::ContentTypeHeader, strContentType);

    QNetworkReply *reply = this->pManager->post(request, queries.query(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QIODevice::readyRead, [reply, functor, failFunctor]() {

        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(reply->error() == QNetworkReply::NoError && httpStatusCode >= 200 && httpStatusCode < 300) {
            functor(reply, httpStatusCode);
        } else {
            failFunctor(reply, httpStatusCode);
        }

        reply->deleteLater();
    });
}

QNetworkRequest star::web::WebAccessManager::generateNormalRequest(const QString &strUrl)
{
    QNetworkRequest request;

    request.setUrl(QUrl(strUrl));
    request.setRawHeader("User-Agent", "StarApplication 3.0");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    return request;
}
