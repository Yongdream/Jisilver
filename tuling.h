#ifndef TULING_H
#define TULING_H

#include <QObject>
#include <QNetworkAccessManager>       //三个http必须头文件
#include <QNetworkReply>
#include <QNetworkRequest>

class Tuling : public QObject
{
public:
    Tuling();
    QNetworkAccessManager *manager;
    QNetworkReply  *reply;
    QNetworkRequest *requst;

    QJsonObject *JsonData;      //封装的json信息

    QString getJson();          //解析返回的json信息
    void Json_data(QString data);           //封装json信息

    void http_connect();
    void doProceesFinished();

private slots:
};

#endif // TULING_H
