#include "tuling.h"
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QJsonObject>    //json
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Tuling::Tuling()
{
    manager = new QNetworkAccessManager(this);
    requst = new QNetworkRequest;
}

/*     HTTP通信   */
void Tuling::http_connect()
{
    requst->setUrl(QUrl("https://api.turingos.cn/turingos/api/v2"));              //填入图灵机器人接口地址
    requst->setHeader(QNetworkRequest::ContentTypeHeader,"application/json");         //设置数据类型为json格式
    QJsonDocument document=QJsonDocument(*JsonData);                                  //将封装的json格式数据转为字节数组形式

    QByteArray array = document.toJson();

    reply = manager->post(*requst,array);                                             //以post方式发送请求
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), //出现异常
          [=](QNetworkReply::NetworkError code)
            {
                qDebug() << code;
                switch((int)code)
                {
                    case QNetworkReply::ConnectionRefusedError:
                        qDebug() << "远程服务器拒绝连接（服务器不接受请求）";
                        break;
                    case QNetworkReply::HostNotFoundError:
                        qDebug() << "找不到远程主机名（无效的主机名）";
                        break;
                    case QNetworkReply::TimeoutError:
                        qDebug() << "与远程服务器的连接超时";
                        break;
                    default:
                        break;
                }
            });
    connect(reply, &QNetworkReply::finished,this,&Tuling::doProceesFinished);

}


/*  封装要发送的json格式信息   */
void Tuling::Json_data(QString data)
{
    QJsonObject provideInfo;
    QJsonObject Text;
    QJsonObject Image;
    QJsonObject Info;
    QJsonObject UserLocation;

    Text.insert("text",data);

    UserLocation.insert("city","杭州");           //后面这一块不必须
    UserLocation.insert("province","浙江");
    UserLocation.insert("street","钱塘区");
    Info.insert("location",UserLocation);
    provideInfo.insert("inputText",Text);
    provideInfo.insert("inputImage",Image);
    provideInfo.insert("selfInfo",Info);

    QJsonObject user;
    user.insert("apiKey","2b244339acb64a3d8a8e1b4455a21ead");     // 填入自己注册的图灵机器人apiKey   必须
    user.insert("userId","378909");                                 //填入 id,必须，否则会显示---没有上传userId!


    JsonData = new QJsonObject;
    JsonData->insert("reqType",0);
    JsonData->insert("perception",provideInfo);      //嵌套
    JsonData->insert("userInfo",user);

    qDebug() << *JsonData;
}

/*  解析返回的json格式信息   */
QString Tuling::getJson()
{
    QByteArray str = reply->readAll();        //获取信息
    qDebug() << "获取信息";
    qDebug() << str;

     QJsonObject json1 = QJsonDocument::fromJson(str).object();
     QJsonArray json2 = json1.value("results").toArray();
     QJsonObject json3 = json2[0].toObject();                 //直接通过下标获取
//     QJsonObject json3;
//     for ( int i = 0; i < json2.size(); i++ )               //循环遍历获取
//     {
//         if ( json2[ i ].isObject() )
//         {
//            json3 = json2[i].toObject();
//            qDebug() << i;
//         }
//     }
     QJsonObject json4 = json3.value("values").toObject();
     QString text = json4.value("text").toString();

     return text;
}

void Tuling::doProceesFinished()
{
    qDebug() <<"结束";
}
