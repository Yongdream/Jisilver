#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QObject>

class Analogclock : public QObject
{
    Q_OBJECT
public:
    explicit Analogclock(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ANALOGCLOCK_H