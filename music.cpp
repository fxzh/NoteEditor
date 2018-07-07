#include <mainwindow.h>

void MainWindow::PlayMusic()
{
    playZt=playZt*(-1);
    emit sendPlayZt(playZt,slid->value());
    if(playZt==-1)
    {
        paintzt=1;
        emit sendTh3Exit();
        PlayAction->setIcon(QIcon(":/img/play.png"));
        labvis->setMouseTracking(true);
    }
    else if(playZt==1)
    {
        emit sendBeginTime(slid->value());
        th3->start();
        PlayAction->setIcon(QIcon(":/img/pause.png"));
        labvis->setMouseTracking(false);
    }
    th2->start();
}

void MainWindow::changeSlidForMusic()
{
//    qd()<<th2->MusicMp3->position();
    int cslidmusic=th2->MusicMp3->position();
    slid->setValue(cslidmusic);
}
