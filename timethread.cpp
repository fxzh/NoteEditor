#include "timethread.h"

timethread::timethread()
{

}

void timethread::beginTime(int a)
{
    musicFirstTime=a;
}

void timethread::run()
{
    th3ExitFlag=0;
    musicTime.start();
//    int ci=0;
    while(th3ExitFlag==0)
    {
        this->msleep(videoDelay);
        emit getMusicPosition();
        whileLoop=0;
        while(whileLoop==0)
        {
            this->msleep(1);
        }
/*        ci++;
        if(ci==200)
        {
            qd()<<"帧:"<<200000.0/(musicTime.restart());
            ci=0;
            musicTime.start();
        }*/
    }
}

void timethread::exitTh3()
{
    th3ExitFlag=1;
}

void timethread::getVideoDelay(int a)
{
    videoDelay=a;
}

void timethread::exitWhile()
{
    whileLoop=1;
}
