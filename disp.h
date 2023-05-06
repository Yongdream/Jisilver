#ifndef DISP_H
#define DISP_H

#include <QWidget>

#include <QPainter>
#include <QtMath>

class disp : public QWidget
{
    Q_OBJECT
public:
    explicit disp(QWidget *parent = nullptr);

public:
    void setvalues(qreal iValues);
    void paintEvent(QPaintEvent *event) override;

private:
    qreal Values;
    const static int radius;
    const static int maxv;
    const static int minv;



signals:

public slots:
};

#endif // DISP_H
