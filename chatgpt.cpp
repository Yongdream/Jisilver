#include "chatgpt.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>

QString ChatGPT::generateReply(const QString &input)
{
    // 设置请求的URL
    QString apiUrl = "https://api.openai.com/v1/engines/davinci-codex/completions";

    // 设置你的 OpenAI API 密钥
    QString apiKey = "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";

    // 构建请求的 JSON 数据
    QJsonObject requestBody;
    requestBody["prompt"] = input;
    requestBody["max_tokens"] = 100;
    requestBody["temperature"] = 0.7;

    QJsonDocument requestDoc(requestBody);
    QByteArray requestData = requestDoc.toJson();

    qDebug() << QString(requestData);

    // 创建网络访问管理器和请求
    QNetworkAccessManager networkManager;
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(apiKey).toUtf8());

    // 发送 POST 请求
    QNetworkReply *reply = networkManager.post(request, requestData);
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 解析响应的 JSON 数据
    QString response;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
        QJsonObject responseObject = responseDoc.object();

        if (responseObject.contains("choices")) {
            QJsonArray choicesArray = responseObject["choices"].toArray();
            if (!choicesArray.isEmpty()) {
                QJsonObject choiceObject = choicesArray.first().toObject();
                response = choiceObject["text"].toString();
            }
        }
    } else {
        // 处理网络请求错误
        response = "网络请求错误: " + reply->errorString();
    }

    // 清理资源
    reply->deleteLater();

    return response;
}
