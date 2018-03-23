#ifndef SECTHREAD_H
#define SECTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QMediaPlayer>
#include <timethread.h>
#define qd qDebug

class secthread : public QThread
{
    Q_OBJECT
public:
    int paintZt;
    QString pathMusic;
    secthread();
    QMediaPlayer *MusicMp3;
    int PlayZt;//-1:需要暂停播放/1：需要播放
    int a=0;
signals:
    void sendMainMusic(int);
protected:
    void run();
public slots:
    void setPaintZt(int);
    void setPathMusic(QString);
    void setPlayZt(int a, int b);
    void getMusic();
};

#endif // SECTHREAD_H
