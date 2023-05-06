#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QtDebug>

class Http : public QObject
{
    Q_OBJECT
public:
    explicit Http(QObject *parent = nullptr);

    int getLastStateCode();

    bool post_syn(const QString &url, QMap<QByteArray, QByteArray> headerdata, QByteArray data, QByteArray &replydata);

signals:

public slots:
private:
    int mystatecode;
};

#endif // HTTP_H
