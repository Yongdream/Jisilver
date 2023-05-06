#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pushBut->setText("按住说话");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushBut_pressed()
{
    ui->pushBut->setText("我正在听");

    audio = new Audio;
    audio->startAudio("E:\\Sail\\Course\\IoT\\JisilverAudio\\demo.pcm");

}

void Widget::on_pushBut_released()
{
    audio->stopAudio();
    ui->pushBut->setText("开始识别");

    // 识别
    speech = new Speech;
    QString text = speech->speechIdentify("E:\\Sail\\Course\\IoT\\JisilverAudio\\demo.pcm");

    ui->textEdit->setText(text);

    ui->pushBut->setText("按住说话");
}

void Widget::on_clearBut_clicked()
{
    ui->textEdit->clear();
}
