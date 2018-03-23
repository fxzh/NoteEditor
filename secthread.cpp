#include "secthread.h"

secthread::secthread()
{

}

void secthread::run()
{
    if(PlayZt==-1)
    {
        MusicMp3->pause();
        paintZt=1;
    }
    else if(PlayZt==1)
    {
        MusicMp3->play();
        paintZt=3;
    }
}

void secthread::setPaintZt(int a)
{
    paintZt=a;
}

void secthread::setPathMusic(QString a)
{
    pathMusic=a;
    MusicMp3=new QMediaPlayer(this);
    MusicMp3->setMedia(QUrl::fromLocalFile(pathMusic));
}

void secthread::setPlayZt(int a,int b)
{
    PlayZt=a;
    MusicMp3->setPosition(b);
}

void secthread::getMusic()
{
    emit sendMainMusic(MusicMp3->position());
/*    if(MusicMp3->position()-a<4)
        qd()<<MusicMp3->position()-a;
    a=MusicMp3->position();*/
}
