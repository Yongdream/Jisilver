#ifndef CHATGPTCLIENT_H
#define CHATGPTCLIENT_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class ChatGPTClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatGPTClient(QObject *parent = nullptr);

    void sendMessage(const QString& message);

signals:
    void messageReceived(const QString& message);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
};

#endif // CHATGPTCLIENT_H
