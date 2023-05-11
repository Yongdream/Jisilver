#include "chatgptclient.h"

ChatGPTClient::ChatGPTClient(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &ChatGPTClient::onReplyFinished);
}

void ChatGPTClient::sendMessage(const QString& message)
{
    QNetworkRequest request(QUrl("https://api.openai.com/v1/engines/davinci-codex/completions"));

    QByteArray postData;
    postData.append("prompt=" + message.toUtf8());
    postData.append("&max_tokens=100");
    // 添加其他需要的参数或头部信息，用于 ChatGPT API

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 添加其他需要的头部信息，用于 ChatGPT API

    // 将 "YOUR_API_KEY" 替换为你的实际 OpenAI API 密钥
    request.setRawHeader("Authorization", "Bearer YOUR_API_KEY");

    networkManager->post(request, postData);
}

void ChatGPTClient::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QString response = reply->readAll();
        // 根据需求解析和处理响应数据

        emit messageReceived(response);
    }
    else
    {
        // 处理错误情况
        // 例如，可以通过调用 reply->errorString() 获取错误信息
    }

    reply->deleteLater();
}
