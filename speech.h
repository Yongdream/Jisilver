#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include "http.h"
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QFile>
#include <QHostInfo>
#include <QMessageBox>

// 获取百度access_token
const QString baiduTokenUrl = "http://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString baiduTokenId = "0IhQOkkS3iglBl9LN4dDefAl";
const QString baiduTokenSecret = "eKh7a9DryCtS4kruakh2q6Mwbq7UOLt9";

// 语音识别相关
const QString baiduspeechUrl = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";



class Speech : public QObject
{
    Q_OBJECT
public:
    explicit Speech(QObject *parent = nullptr);

    QString speechIdentify(QString filename);
    QString getJsonvalue(QByteArray replydata, QString key);

signals:

public slots:

private:
    bool genFileByByteArray(QByteArray replydata, QString filename);
};

#endif // SPEECH_H
