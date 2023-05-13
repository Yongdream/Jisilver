#include "http.h"

Http::Http(QObject *parent) : QObject(parent)
{
    mystatecode = 0;
}

int Http::getLastStateCode()
{
    return mystatecode;
}

bool Http::post_syn(const QString &url, QMap<QByteArray, QByteArray> headerdata, QByteArray data, QByteArray& replydata)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;

    request.setUrl(url);
    // 迭代器遍历对象
    QMapIterator<QByteArray, QByteArray> map(headerdata);
    while (map.hasNext()) {
        map.next();
        request.setRawHeader(map.key(), map.value());
    }
    QNetworkReply *reply = manager.post(request, data);

    // 不能立即响应 等待服务器返回
    QEventLoop l;
    connect(reply, SIGNAL(finished()), &l, SLOT(quit()));
    l.exec();

//    qDebug()<< QSslSocket::sslLibraryBuildVersionString();
//    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

    if(reply != nullptr && reply->error() == QNetworkReply::NoError)
    {
        replydata = reply->readAll();
//        qDebug()  << replydata;
        QString ss = reply->header(QNetworkRequest::ContentTypeHeader).toString();
        mystatecode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    }
    else{
        QNetworkReply::NetworkError error = reply->error();
        QString serror = reply->errorString();
        qDebug() << "请求失败";
        qDebug()  << serror;
        return false;
        }
}
