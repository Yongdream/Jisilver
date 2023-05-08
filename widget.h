#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "audio.h"
#include "speech.h"

#include <QPaintEvent>	//绘图事件
#include <QDebug>		//测试
#include <QPainter>	//画家
#include <QPen>	//笔
#include <QBrush>	//画刷
#include <QPoint>	//点
#include <QTime>	//能系统时间
#include <QTimer>	//定时器


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

private:
    Ui::Widget *ui;
    Audio *audio;
    Speech *speech;

};

#endif // WIDGET_H
