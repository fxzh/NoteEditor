#include <mainwindow.h>

void MainWindow::mousePressEvent(QMouseEvent *pe)
{
    if(paintzt!=0&&labvis->hasMouseTracking()==true)
    {
        double bpmeffect=bpmTable->item(mouseLabBpmTable,2)->data(0).toDouble();
        if(pe->button()==Qt::LeftButton)
        {
            if(MouseInLabvis==1)
            {
                if(editZt==1||editZt==2||editZt==3)
                {
//                    qd()<<"eff"<<bpmeffect<<dtForPress;
                    pressTime=int(dtForPress+int((labvis4-dpxForPress-labMouseY)/\
                                                         double(bh*bpmeffect))*dSmallbarTime);
                    pressPos=5*labMouseX/double(labvis3)-2.5;
                    addNote();
                }
                else if(editZt==4||editZt==5)
                {
                    if(longEditZt==0)//long note 起始
                    {
                        longEditZt=1;
                        pressTime=int(dtForPress+int((labvis4-dpxForPress-labMouseY)/\
                                                             (bh*bpmeffect))*dSmallbarTime);
                        pressPos=5*labMouseX/double(labvis3)-2.5;
                        fixEditPointX=editPoint1.x();
                        fixEditPointX2=editPoint2.x();
                    }
                    else if(longEditZt==1)//long note 结束
                    {
                        longEditZt=0;
                        pressTime2=int(dtForPress+int((labvis4-dpxForPress-labMouseY)/\
                                                              (bh*bpmeffect))*dSmallbarTime);
                        addNote();
                    }
                }
                else if(editZt==6)
                {
                    pressTime=int(dtForPress+int((labvis4-dpxForPress-labMouseY)/\
                                                         double(bh*bpmeffect))*dSmallbarTime);
                    int index=searchBpmNote(pressTime);
                    if(index==-1)
                    {
                        addBpmNote();
                        searchBpmIndex(slid->value());
           /*             for(int i=0;i<bpmTable->rowCount();i++)
                        {
                            for(int j=0;j<5;j++)
                            {
                                qs<<bpmTable->item(i,j)->data(0);
                            }
                        }
                        qs<<endl;*/
                    }
                    else
                    {
                        changeBpmNote(index);
                    }
                }
            }
        }
        else if(pe->button()==Qt::RightButton)
        {
            if(MouseInLabvis==1)
            {
                delPressTime1=int(dtForPress+int((labvis4-dpxForPress-labMouseY)/\
                                                         (bh*bpmeffect))*dSmallbarTime);
                delPressTime2=int(dtForPress+int((labvis4-dpxForPress-labMouseY)/\
                                                         (bh*bpmeffect)+1)*dSmallbarTime);
                if(editZt!=0&&editZt!=6)
                {
                    pressPos=5*labMouseX/double(labvis3)-2.5;
                    int a=searchPressNote(delPressTime1,delPressTime2,pressPos);
                    if(a!=-1)
                    {
                        deleteNote(a);
                    }
                }
                else if(editZt==6)
                {
                    int a=searchBpmNote2(delPressTime1,delPressTime2);
                    if(a!=-1)
                    {
                        deleteBpmNote(a);
                        searchBpmIndex(slid->value());
/*                        ttemp=1;
                        for(int i=0;i<bpmTable->rowCount();i++)
                        {
                            for(int j=0;j<5;j++)
                            {
                                qs<<bpmTable->item(i,j)->data(0);
                            }
                        }*/
                    }
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
