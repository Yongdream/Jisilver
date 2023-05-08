#include "widget.h"
#include "ui_widget.h"

bool isEng = true;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pushBut->setText("按住说话");
    ui->swiBut->setText("中文");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushBut_pressed()
{
    ui->pushBut->setText("我正在听");

    QIcon icon;
    icon.addFile(tr("E:\\Sail\\Course\\IoT\\Jisilver\\Jisilver\\icon\\voice.png"));
    ui->pushBut->setIcon(icon);

    audio = new Audio;
    audio->startAudio("E:\\Sail\\Course\\IoT\\JisilverAudio\\demo.pcm");

}

void Widget::on_pushBut_released()
{
    audio->stopAudio();
    ui->pushBut->setText("开始识别");

    // 识别
    speech = new Speech;
    QString text = speech->speechIdentify("E:\\Sail\\Course\\IoT\\JisilverAudio\\demo.pcm", isEng);

    ui->textEdit->setText(text);

    ui->pushBut->setText("按住说话");
}

void Widget::on_clearBut_clicked()
{
    ui->textEdit->clear();
}

void Widget::on_swiBut_pressed()
{
    isEng = !isEng;
    if (isEng) {
        ui->swiBut->setText("中文");
    } else {
        ui->swiBut->setText("En");
    }
}
