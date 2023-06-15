#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "audio.h"
#include "speech.h"
#include "chatgpt.h"
#include "tuling.h"

#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushBut_pressed();

    void on_pushBut_released();

    void on_clearBut_clicked();

    void on_swiBut_pressed();

    void processText();

    void on_finished_clicked();//调用JavaScript里面的函数
    
    void on_btnmapA_clicked();

private:
    Ui::Widget *ui;
    Audio *audio;
    Speech *speech;
    Tuling *tuling;

    QPushButton *sendButton;
    QLineEdit *inputField;
    QTextEdit *chatWindow;

};

#endif // WIDGET_H
