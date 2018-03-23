#include <mainwindow.h>

void MainWindow::mousePressEvent(QMouseEvent *pe)
{
    if(paintzt!=0)
    {
        if(pe->button()==Qt::LeftButton)
        {
            if(MouseInLabvis==1)
            {
                if(editZt==1||editZt==2||editZt==3)
                {
                    pressTime=int(dFirstSmallbarTime+int((labvis4-dFirstSmallpx-labMouseY)/bh)*dSmallbarTime);
                    pressPos=5*labMouseX/double(labvis3)-2.5;
                    addNote();
                }
                else if(editZt==4||editZt==5)
                {
                    if(longEditZt==0)//long note 起始
                    {
                        longEditZt=1;
                        pressTime=int(dFirstSmallbarTime+int((labvis4-dFirstSmallpx-labMouseY)/bh)*dSmallbarTime);
                        pressPos=5*labMouseX/double(labvis3)-2.5;
                    }
                    else if(longEditZt==1)//long note 结束
                    {
                        longEditZt=0;
                        pressTime2=int(dFirstSmallbarTime+int((labvis4-dFirstSmallpx-labMouseY)/bh)*dSmallbarTime);
                        addNote();
                    }
                }
            }
        }
        else if(pe->button()==Qt::RightButton)
        {
            if(MouseInLabvis==1&&editZt!=0)
            {
                delPressTime1=int(dFirstSmallbarTime+int((labvis4-dFirstSmallpx-labMouseY)/bh)*dSmallbarTime);
                delPressTime2=int(dFirstSmallbarTime+int((labvis4-dFirstSmallpx-labMouseY)/bh+1)*dSmallbarTime);
                pressPos=5*labMouseX/double(labvis3)-2.5;
                int a=searchPressNote(delPressTime1,delPressTime2,pressPos);
                if(a!=-1)
                {
                    deleteNote(a);
                }
            }
        }
    }
}

void MainWindow::wheelEvent(QWheelEvent *we)
{
    if(MouseInLabvis==1)
    {
        if(we->delta()<0)
        {
            slid->setValue(slid->value()-whd);
            if(slid->value()<slid->minimum())
                slid->setValue(slid->minimum());
        }
        else
        {
            slid->setValue(slid->value()+whd);
            if(slid->value()>slid->maximum())
                slid->setValue(slid->maximum());
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *me)
{
    if(paintzt!=0)
    {
        if(me->x()>=labvis1&&me->x()<=labvis1+labvis3&&me->y()>=labvis2&&me->y()<=labvis2+labvis4)
        {
            MouseInLabvis=1;
            labMouseX=me->x()-labvis1;
            labMouseY=me->y()-labvis2;
            editBeforePaint();
        }
        else
            MouseInLabvis=0;
    }
}
