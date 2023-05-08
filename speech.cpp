#include "speech.h"

Speech::Speech(QObject *parent) : QObject(parent)
{

}

QString Speech:: speechIdentify(QString filename, bool isEn)
{
    QString accessToken;

    QByteArray requestdata, replydata;
    // 获取access_token
    QString tokenUrl = QString(baiduTokenUrl).arg(baiduTokenId).arg(baiduTokenSecret);

    QMap<QByteArray, QByteArray> headers;
    headers.insert(QString("Content-Type").toLatin1(), QString("audio/pcm;rate=16000").toLatin1());

    Http myhttp;
    // 一次请求
    bool success = myhttp.post_syn(tokenUrl, headers, requestdata, replydata);
    if (success)
    {
        QString key = "access_token";
        accessToken = getJsonvalue(replydata, key);
//        qDebug() << accessToken;
//        return accessToken;
    }
    else
    {
        QMessageBox::warning(NULL,"请求提示","请求失败");
    }

    // 识别语音
    QString speechUrl;
    if (isEn == true)
    {
       speechUrl = QString(baiduspeechUrl).arg(QHostInfo::localHostName()).arg(accessToken);
    }
    else
    {
       speechUrl = QString(baiduspeechUrlEn).arg(QHostInfo::localHostName()).arg(accessToken);
    }
    qDebug() << speechUrl;


    // 文件转QByteArray
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    requestdata = file.readAll();
    file.close();

    replydata.clear();

    // 二次请求
    bool success2 = myhttp.post_syn(speechUrl, headers, requestdata, replydata);
    if (success2)
    {
        QString key = "result";
        QString text = getJsonvalue(replydata, key);
        qDebug() << text;
        return text;
    }
    else
    {
        QMessageBox::warning(NULL,"识别提示","识别失败");
    }

    return "";
}

QString Speech::getJsonvalue(QByteArray replydata, QString key)
{
    QJsonParseError jsonerror;
    QJsonDocument json_document = QJsonDocument::fromJson(replydata, &jsonerror);
    if(jsonerror.error == QJsonParseError::NoError)
    {
        if (json_document.isObject())
        {
            // json_document转换为json对象
            QJsonObject json_object = json_document.object();
            if (json_object.contains(key))
            {
                QJsonValue json_value = json_object.value(key);
                if (json_value.isString())
                {
                   return json_value.toString() ;
                }
                else if (json_value.isArray())
                {
                    QJsonArray arr = json_value.toArray();  // 转换成array
                    QJsonValue jv = arr.at(0);              // 获取第一个元素
                    return jv.toString();
                }
            }
        }
    }
    return "";
}


bool Speech::genFileByByteArray(QByteArray replydata, QString filename)
{
    QFile file(filename);
    bool success = file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if (success)
    {
        file.write(replydata);
        file.close();
        return true;
    }
    return false;
}
