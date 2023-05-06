#include "audio.h"

Audio::Audio(QObject *parent) : QObject(parent)
{

}

void Audio::startAudio(QString filename)
{
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    if(device.isNull())
    {
        QMessageBox::warning(NULL, "QAudioDeviceInfo:", "未找到录音设备");
    }
    else
    {
        // 设置音频编码要求
        QAudioFormat myformat;
        myformat.setSampleRate(16000);
        myformat.setChannelCount(1);
        myformat.setSampleSize(16);
        myformat.setCodec("audio/pcm");

        // 判断设备是否支持该格式
        if (!device.isFormatSupported(myformat))
        {
            myformat = device.nearestFormat(myformat);
        }

        // 打开文件写入
        myfile = new QFile;
        myfile->setFileName(filename);
        myfile->open(QIODevice::WriteOnly);

        // 创建录音文件
        myaudio = new QAudioInput(myformat, this);
        myaudio->start(myfile);
    }


}

void Audio::stopAudio()
{
    myaudio->stop();

    myfile->close();
    delete myfile;
    myfile = NULL;
}
