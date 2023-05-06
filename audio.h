#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QMessageBox>
#include <QAudioInput>
#include <QFile>

class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = nullptr);

    void startAudio(QString filename);
    void stopAudio();

signals:

public slots:

private:
    QAudioInput *myaudio;
    QFile *myfile;
};

#endif // AUDIO_H
