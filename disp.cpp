#include "disp.h"

const int disp::radius = 150;
const int disp::maxv = 0;
const int disp::minv = 400;

disp::disp(QWidget *parent) : QWidget(parent)
{
    Values = 0;

}

void disp::setvalues(qreal iValues)
{
    Values = iValues;
    update();
}

void disp::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPoint center(width()/2,height()/2);
    painter.save();




}
