#include <mainwindow.h>

void MainWindow::paintEvent(QPaintEvent *e)
{
    testTime.start();times++;//int a,b,c,d;
    Q_UNUSED(e);
/*    if(ttemp>=1)
        qs<<"ac";
    if(ttemp==1)
        qs<<paintBpmIndex1<<paintBpmIndex2;*/
    if(paintzt==1||paintzt==3)
    {
        pix=QPixmap(labvis3,labvis4);
        QPainter pan(&pix);
        pan.setPen(QColor(255,255,255,0));
        pan.setBrush(QBrush(QColor(255,255,255)));
        pan.drawRect(0,0,labvis3,labvis4);
        double tempsmallpx;
        int tempsmalltime;
        int bpmnonepx=0;
        for(int i=paintBpmIndex1;i<=paintBpmIndex2;i++)
        {
            //计算各bpm的起始点,终点
            int bpmtime=bpmTable->item(i,0)->data(0).toInt();
            double thisbpm=bpmTable->item(i,1)->data(0).toDouble();
            double bpmeffect=bpmTable->item(i,2)->data(0).toDouble();
            int bpmbeat=bpmTable->item(i,3)->data(0).toInt();
            int bpmcon=bpmTable->item(i,4)->data(0).toInt();
            if(i==paintBpmIndex1)
            {
                bpmnonepx=(bpmtime-slid->value())*(bh*thisbpm*smallbars*bpmeffect/1250.0/192.0);
            }
            int bebpmpx=bpmnonepx;
            int a=inPaint(bpmtime,thisbpm,bpmeffect,bpmbeat,bpmcon,bpmnonepx);
            bpmnonepx=a;
            editPoint1.setY(int(labvis4-dFirstSmallpx-int((labvis4-dFirstSmallpx-labMouseY)/\
                                                          (bh*bpmeffect))*(bh*bpmeffect)));
            editPoint1.setX(labMouseX-dNoteWidth*labvis3/10);
            editPoint2.setY(int(labvis4-dFirstSmallpx-int((labvis4-dFirstSmallpx-labMouseY)/\
                                                          (bh*bpmeffect))*(bh*bpmeffect)));
            editPoint2.setX(labMouseX+dNoteWidth*labvis3/10);

            //画灰线
            pan.setPen(QColor(220,220,220));
            tempsmallpx=labvis4-dFirstSmallpx;
            while(tempsmallpx>labvis4-bpmnonepx&&tempsmallpx>=0)
            {
                pan.drawLine(0,int(tempsmallpx),labvis3,int(tempsmallpx));
                tempsmallpx=tempsmallpx-double(bh*bpmeffect);
            }
            //画灰黑线
            if(smallbar->currentIndex()!=0&&smallbar->currentIndex()!=1&&\
                    smallbar->currentIndex()!=2&&smallbar->currentIndex()!=4)
            {
                double tempMidpx=labvis4-dFirstMidpx;
                pan.setPen(QColor(130,130,130));
                while(tempMidpx>labvis4-bpmnonepx)
                {
                    pan.drawLine(0,tempMidpx,labvis3,tempMidpx);
                    tempMidpx=tempMidpx-double(bh*bpmeffect*smallbars/4.0);
                }
            }
            //画黑线
            double tempbigpx=labvis4-dFirstBigpx;
            pan.setPen(QColor(0,0,0));
            while(tempbigpx>labvis4-bpmnonepx)
            {
                pan.drawLine(0,tempbigpx,labvis3,tempbigpx);
                tempbigpx=tempbigpx-double(bh*bpmeffect*smallbars);
            }
            //画note
            for(int i=1;i<=tw->rowCount();i++)
            {
                if(tw->item(i-1,1)->data(0).toInt()>dLastSmallbarTime||tw->item(i-1,1)->data(0).toInt()>bpmLastTime)
                {
                    break;
                }
                else if(tw->item(i-1,1)->data(0).toInt()+tw->item(i-1,4)->data(0).toInt()>dFirstSmallbarTime-70)
                {
                    double dNoteTimepx,dNoteCanAddTimepx,dLeftPoint,dRightPoint;
                    int NoteTimepx,NoteCanAddTimepx,LeftPoint,RightPoint;
                    if(tw->item(i-1,1)->data(0).toInt()<dFirstSmallbarTime)
                    {
                        dNoteTimepx=labvis4-((dFirstSmallbarTime-bpmtime)\
                                             *(bh*bpmeffect*thisbpm*smallbars/1250.0/192.0)+bebpmpx);
                    }
                    else
                    {
                        dNoteTimepx=labvis4-((tw->item(i-1,1)->data(0).toInt()-bpmtime)\
                                             *(bh*bpmeffect*thisbpm*smallbars/1250.0/192.0)+bebpmpx);
                    }

                    if(tw->item(i-1,1)->data(0).toInt()+tw->item(i-1,4)->data(0).toInt()>bpmLastTime)
                    {
                        dNoteCanAddTimepx=labvis4-((bpmLastTime\
                                                 -bpmtime)*(bh*bpmeffect*thisbpm*smallbars/1250.0/192.0)+bebpmpx);
                    }
                    else
                    {
                        dNoteCanAddTimepx=labvis4-((tw->item(i-1,1)->data(0).toInt()+tw->item(i-1,4)->data(0).toInt()\
                                                 -bpmtime)*(bh*bpmeffect*thisbpm*smallbars/1250.0/192.0)+bebpmpx);
                    }

                    dLeftPoint=(tw->item(i-1,2)->data(0).toDouble()\
                                -0.5*tw->item(i-1,3)->data(0).toDouble()+2.5)*labvis3/5.0;
                    dRightPoint=(tw->item(i-1,2)->data(0).toDouble()\
                                +0.5*tw->item(i-1,3)->data(0).toDouble()+2.5)*labvis3/5.0;
                    LeftPoint=dLeftPoint;
                    RightPoint=dRightPoint;
                    NoteTimepx=dNoteTimepx;
                    NoteCanAddTimepx=dNoteCanAddTimepx;
                    if(tw->item(i-1,0)->data(0).toInt()==0)
                    {
                        pan.setPen(QColor(0,53,236));
                        pan.setBrush(QBrush(QColor(0,53,236,255)));
                        pan.drawRect(LeftPoint,NoteTimepx-9,RightPoint-LeftPoint,8);
                    }
                    else if(tw->item(i-1,0)->data(0).toInt()==1)
                    {
                        pan.setPen(QColor(255,153,15));
                        pan.setBrush(QBrush(QColor(255,153,15,255)));
                        pan.drawRect(LeftPoint,NoteTimepx-9,RightPoint-LeftPoint,8);
                    }
                    else if(tw->item(i-1,0)->data(0).toInt()==2)
                    {
                        pan.setPen(QColor(255,15,225));
                        pan.setBrush(QBrush(QColor(255,15,225,255)));
                        pan.drawRect(LeftPoint,NoteTimepx-9,RightPoint-LeftPoint,8);
                    }
                    else if(tw->item(i-1,0)->data(0).toInt()==3)
                    {
                        pan.setPen(QColor(0,255,64));
                        pan.setBrush(QBrush(QColor(0,255,64,200)));
                        pan.drawRect(LeftPoint,NoteCanAddTimepx,RightPoint-LeftPoint,NoteTimepx-NoteCanAddTimepx);
                    }
                    else if(tw->item(i-1,0)->data(0).toInt()==4)
                    {
                        pan.setPen(QColor(255,255,0));
                        pan.setBrush(QBrush(QColor(255,255,0,200)));
                        pan.drawRect(LeftPoint,NoteCanAddTimepx,RightPoint-LeftPoint,NoteTimepx-NoteCanAddTimepx);
                    }
                    //画击打特效
                    if(tw->item(i-1,0)->data(0).toInt()<=2)
                    {
                        if(NoteTimepx>=labvis4&&NoteTimepx<=labvis4+40)
                        {
                            seScaredPix=sePix.scaled(RightPoint-LeftPoint,labvis4);
                            pan.drawPixmap(LeftPoint,0,seScaredPix);
                        }
                    }
                    else if(tw->item(i-1,0)->data(0).toInt()>=3)
                    {
                        if(NoteTimepx>=labvis4&&NoteCanAddTimepx<=labvis4)
                        {
                            seScaredPix=sePix.scaled(RightPoint-LeftPoint,labvis4);
                            pan.drawPixmap(LeftPoint,0,seScaredPix);
                        }
                    }
                }
            }
            //画变bpm标识
            for(int i=0;i<bpmTable->rowCount();i++)
            {
                if(bpmTable->item(i,0)->data(0).toInt()>=bpmLastTime)
                {
                    break;
                }
                else if(bpmTable->item(i,0)->data(0).toInt()>dFirstSmallbarTime-70)
                {
                    double dNoteTimepx;
                    int NoteTimepx;
                    dNoteTimepx=labvis4-((bpmTable->item(i,0)->data(0).toInt()-bpmtime)\
                                             *(bh*bpmeffect*thisbpm*smallbars/1250.0/192.0)+bebpmpx);
                    NoteTimepx=dNoteTimepx;
                    QString aa=QString("%1").arg(bpmTable->item(i,2)->data(0).toDouble());
                    aa.insert(0,"*");
                    aa.insert(0,QString("%1").arg(bpmTable->item(i,1)->data(0).toDouble()));
                    pan.setPen(QColor(0,0,0));
                    pan.drawText(labvis3-100,NoteTimepx-20,100,20,Qt::AlignRight,aa);
                }
            }
            //画虚note
            if(MouseInLabvis==1&&labMouseY>labvis4-bpmnonepx&&labMouseY<=labvis4-bebpmpx)
            {
                mouseLabBpmTable=i;
                dtForPress=dFirstSmallbarTime;
                dpxForPress=dFirstSmallpx;
                if(editZt==1)
                {
                    pan.setPen(QColor(0,53,236));
                    pan.setBrush(QBrush(QColor(0,53,236,128)));
                    pan.drawRect(editPoint1.x(),editPoint1.y()-8,editPoint2.x()-editPoint1.x(),8);
                }
                else if(editZt==2)
                {
                    pan.setPen(QColor(255,153,15));
                    pan.setBrush(QBrush(QColor(255,153,15,128)));
                    pan.drawRect(editPoint1.x(),editPoint1.y()-8,editPoint2.x()-editPoint1.x(),8);
                }
                else if(editZt==3)//滑
                {
                    pan.setPen(QColor(255,15,225));
                    pan.setBrush(QBrush(QColor(255,15,225,128)));
                    pan.drawRect(editPoint1.x(),editPoint1.y()-8,editPoint2.x()-editPoint1.x(),8);
                }
                else if(editZt==4)
                {
                    pan.setPen(QColor(0,255,64));
                    pan.setBrush(QBrush(QColor(0,255,64,100)));
                    if(longEditZt==0)
                    {
                        pan.drawRect(editPoint1.x(),editPoint1.y()-8,editPoint2.x()-editPoint1.x(),8);
                    }
                    else
                    {
                        moveTime2=int(dFirstSmallbarTime\
                                      +int((labvis4-dFirstSmallpx-labMouseY)/(bh*bpmeffect))*dSmallbarTime);
                        moveLongNotePx=int((bh*bpmeffect)*(moveTime2-pressTime)/dSmallbarTime);
                        pan.drawRect(fixEditPointX,editPoint1.y(),fixEditPointX2-fixEditPointX,moveLongNotePx);
                    }
                }
                else if(editZt==5)
                {
                    pan.setPen(QColor(255,255,0));
                    pan.setBrush(QBrush(QColor(255,255,0,100)));
                    if(longEditZt==0)
                    {
                        pan.drawRect(editPoint1.x(),editPoint1.y()-8,editPoint2.x()-editPoint1.x(),8);
                    }
                    else
                    {
                        moveTime2=int(dFirstSmallbarTime\
                                      +int((labvis4-dFirstSmallpx-labMouseY)/(bh*bpmeffect))*dSmallbarTime);
                        moveLongNotePx=int((bh*bpmeffect)*(moveTime2-pressTime)/dSmallbarTime);
                        pan.drawRect(fixEditPointX,editPoint1.y(),fixEditPointX2-fixEditPointX,moveLongNotePx);
                    }
                }
                else if(editZt==6)
                {
                    pan.setPen(QColor(0,0,0));
                    pan.setBrush(QBrush(QColor(0,0,0,255)));
                    pan.drawText(labvis3-100,editPoint1.y()-15,100,15\
                                 ,Qt::AlignRight,editBpm->text()+"*"+editBpm2->text());
                }
            }
            //画时间
            double dtempsmalltime=dFirstSmallbarTime;
            tempsmallpx=labvis4-dFirstSmallpx;
            pan.setPen(QColor(0,0,0));
            while(tempsmallpx>labvis4-bpmnonepx)
            {
                tempsmalltime=dtempsmalltime;
                pan.drawText(QPoint(0,tempsmallpx),QString("%1").arg(tempsmalltime));
                tempsmallpx=tempsmallpx-double(bh*bpmeffect);
                dtempsmalltime=dtempsmalltime+dSmallbarTime;
            }
        }
        labvis->setPixmap(pix);
        labvis->show();
        if(paintzt==1)
            paintzt=2;
        emit th3ExitLoop();
    }
    if(ttemp==1)
    {
        qs<<"ae";
    }
}

void MainWindow::resizeEvent(QResizeEvent *rese)
{
    Q_UNUSED(rese);
    scrh=this->height();
    scrw=this->width();
    if(paintzt==2)
    {
        QRect recttw(0,menuh+toolh,twliew,scrh-stah-55);
        tw->setGeometry(recttw);
        slid1=scrw-50;
        slid4=scrh-slid2-50;
        slid->setGeometry(slid1,slid2,slid3,slid4);
        labvis3=scrw-labvis1-slid3-30;
        labvis4=scrh-stah-labvis2-20;
        QRect relabvis(labvis1,labvis2,labvis3,labvis4);
        labvis->setGeometry(relabvis);
        beforepaint();
        paintzt=1;
    }
}

void MainWindow::beforepaint()
{
    dZtime=zongtime;
    dBigbarTime=240000/bpm;
    BigbarTime=dBigbarTime;
    dSmallbarTime=240000/bpm/smallbars;
    SmallbarTime=dSmallbarTime;
    dFirstSmallbarTime=dSmallbarTime*int(slid->value()/dSmallbarTime);
    FirstSmallbarTime=dFirstSmallbarTime;
    dFirstSmallpx=(bh*effect)/dSmallbarTime*(dFirstSmallbarTime-slid->value());
    FirstSmallpx=dFirstSmallpx;
    dFirstBigbarTime=dBigbarTime*int(slid->value()/dBigbarTime);
    FirstBigbarTime=dFirstBigbarTime;
    dFirstBigpx=(bh*effect)/dSmallbarTime*(dFirstBigbarTime-slid->value());
    FirstBigpx=dFirstBigpx;
    dLastSmallbarTime=dFirstSmallbarTime+labvis4*dSmallbarTime/(bh*effect);
    LastSmallbarTime=dLastSmallbarTime;
//    dSlidValueTop=slid->value()+labvis4*dSmallbarTime/(bh*effect);
    SlidValueTop=dSlidValueTop;
    dMidbarTime=60000/bpm;
    midbarTime=dMidbarTime;
    dFirstMidbarTime=dMidbarTime*int(slid->value()/dMidbarTime);
    firstMidbarTime=dFirstMidbarTime;
    dFirstMidpx=(bh*effect)/dSmallbarTime*(dFirstMidbarTime-slid->value());
    firstMidpx=dFirstMidpx;
}

int MainWindow::inPaint(int bpmtime,double bpm,double bpmeffect,int bpmbeats,int bpmcon,int bpmnonepx)
{
    dSmallbarTime=240000/bpm/smallbars;SmallbarTime=dSmallbarTime;
    dMidbarTime=60000/bpm;midbarTime=dMidbarTime;
    dBigbarTime=240000/bpm;BigbarTime=dBigbarTime;
    dFirstSmallbarTime=((192/smallbars-bpmbeats%(192/smallbars))%(192/smallbars))*1250/bpm+bpmtime;
    dFirstMidbarTime=((48-bpmbeats%48)%48)*1250/bpm+bpmtime;
    dFirstBigbarTime=((192-bpmbeats%192)%192)*1250/bpm+bpmtime;
    if(dFirstSmallbarTime<slid->value())
    {
        dFirstSmallbarTime=dFirstSmallbarTime+int((slid->value()-dFirstSmallbarTime)/dSmallbarTime)*dSmallbarTime;
    }
    if(dFirstMidbarTime<slid->value())
    {
        dFirstMidbarTime=dFirstMidbarTime+int((slid->value()-dFirstMidbarTime)/dMidbarTime)*dMidbarTime;
    }
    if(dFirstBigbarTime<slid->value())
    {
        dFirstBigbarTime=dFirstBigbarTime+int((slid->value()-dFirstBigbarTime)/dBigbarTime)*dBigbarTime;
    }
    FirstSmallbarTime=dFirstSmallbarTime;firstMidbarTime=dFirstMidbarTime;FirstBigbarTime=dFirstBigbarTime;
    dFirstSmallpx=bh*bpmeffect*bpm*smallbars/1250.0/192.0*(dFirstSmallbarTime-bpmtime)+bpmnonepx;
    FirstSmallpx=dFirstSmallpx;
    dFirstMidpx=bh*bpmeffect*bpm*smallbars/1250.0/192.0*(dFirstMidbarTime-bpmtime)+bpmnonepx;firstMidpx=dFirstMidpx;
    dFirstBigpx=bh*bpmeffect*bpm*smallbars/1250.0/192.0*(dFirstBigbarTime-bpmtime)+bpmnonepx;FirstBigpx=dFirstBigpx;
    dFirstNonePx=bpmnonepx;
    if(bpmcon==-1)
    {
        dBpmConPx=labvis4-bpmnonepx;
        if(bpmtime<slid->value())
        {
            dBpmLastTime=slid->value()+labvis4*240000/bpm/smallbars/bh/bpmeffect;
        }
        else
        {
            dBpmLastTime=bpmtime+(labvis4-bpmnonepx)*240000/bpm/smallbars/bh/bpmeffect;
        }
    }
    else
    {
        dBpmConPx=smallbars*bh*bpmeffect*bpmcon/192.0;
        dBpmLastTime=bpmtime+1250*bpmcon/bpm;
    }
    dLastSmallbarTime=dFirstSmallbarTime+labvis4*(dSmallbarTime/(bh*bpmeffect)+1);
    LastSmallbarTime=dLastSmallbarTime;
    bpmConPx=dBpmConPx;
    bpmLastTime=dBpmLastTime;
    return bpmnonepx+bpmConPx;
}

void MainWindow::musicBeforePaint()
{
    paintzt=1;
    MainWindow::beforepaint();
    MainWindow::paintEvent(painte);
}

void MainWindow::editBeforePaint()
{
    paintzt=1;
    MainWindow::beforepaint();
    editPoint1.setY(int(labvis4-dFirstSmallpx-int((labvis4-dFirstSmallpx-labMouseY)/(bh*effect))*(bh*effect)));
    editPoint1.setX(labMouseX-dNoteWidth*labvis3/10);
    editPoint2.setY(int(labvis4-dFirstSmallpx-int((labvis4-dFirstSmallpx-labMouseY)/(bh*effect))*(bh*effect)));
    editPoint2.setX(labMouseX+dNoteWidth*labvis3/10);
    MainWindow::paintEvent(painte);
}
