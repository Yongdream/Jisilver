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

    QIcon iconVo, iconCl, iconAi;
    iconVo.addFile(tr("E:\\Sail\\Course\\IoT\\Jisilver\\Jisilver\\icon\\voice.png"));
    iconCl.addFile(tr("E:\\Sail\\Course\\IoT\\Jisilver\\Jisilver\\icon\\clear.png"));
    iconAi.addFile(tr("E:\\Sail\\Course\\IoT\\Jisilver\\Jisilver\\icon\\openAI.png"));
    ui->pushBut->setIcon(iconVo);
    ui->clearBut->setIcon(iconCl);
    ui->gatBut->setIcon(iconAi);

    connect(ui->gatBut, &QPushButton::clicked, this, &Widget::processText);
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
    QString text = speech->speechIdentify("E:\\Sail\\Course\\IoT\\JisilverAudio\\demo.pcm", isEng);

    ui->textEdit->setText(text);

    if (text == "作者。")
    {
        ui->textEdit->setText("杨志 吴亚强 李浩瑧");
    }

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

void Widget::processText()
{
    // 从文本框中获取用户输入的文本
    QString userInput = ui->textEdit->toPlainText();
    qDebug() << userInput;

    // 创建 ChatGPT 实例
    ChatGPT chatGpt;

    // 调用 ChatGPT 的处理函数生成回复
    QString reply = chatGpt.generateReply(userInput);

    // 在结果文本框中显示回复
    ui->gptWin->setPlainText(reply);
}
