#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
//#include <QtWebEngineWidgets>
//#include <QWebEngineView>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

public slots:
    void on_finished_clicked(); //调用JavaScript里面的函数
    void on_btnmapA_clicked();
};

#endif // MAINWIDGET_H
