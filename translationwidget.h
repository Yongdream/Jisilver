#ifndef TRANSLATIONWIDGET_H
#define TRANSLATIONWIDGET_H

#include <QObject>
#include <QtNetwork>

class Translationwidget : public QObject
{
    Q_OBJECT
public:
    explicit Translationwidget(QObject *parent = nullptr);
    TranslationWidget(QWidget *parent = nullptr);

signals:

public slots:
    void translateText();
        void handleTranslation(QNetworkReply *reply);
        QString generateSign(const QString &text);
private:
    QTextEdit *inputTextEdit;
    QTextEdit *outputTextEdit;
    QPushButton *translateButton;
};

#endif // TRANSLATIONWIDGET_H
