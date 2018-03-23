#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QObject>
#include <QThread>
#include <QTime>
#include <QDebug>
#define qd qDebug

class timethread : public QThread
{
    Q_OBJECT
public:
    QTime musicTime;
    int musicFirstTime;
    int th3ExitFlag;
    int videoDelay;
    int whileLoop;
    timethread();
signals:
    void getMusicPosition();
public slots:
    void beginTime(int a);
    void exitTh3();
    void getVideoDelay(int a);
    void exitWhile();
protected:
    void run();
};

#endif // TIMETHREAD_H
