#include <mainwindow.h>

void MainWindow::chooseClick1()
{
    MainWindow::choosePreview();
    setClick1->setIcon(QIcon(":/img/click1use.png"));
    editZt=1;
}

void MainWindow::chooseClick2()
{
    MainWindow::choosePreview();
    setClick2->setIcon(QIcon(":/img/click2use.png"));
    editZt=2;
}

void MainWindow::chooseSlid()
{
    MainWindow::choosePreview();
    setSlide->setIcon(QIcon(":/img/sliduse.png"));
    editZt=3;
}

void MainWindow::choosePress1()
{
    MainWindow::choosePreview();
    setPress1->setIcon(QIcon(":/img/press1use.png"));
    editZt=4;
}

void MainWindow::choosePress2()
{
    MainWindow::choosePreview();
    setPress2->setIcon(QIcon(":/img/press2use.png"));
    editZt=5;
}

void MainWindow::chooseBpm()
{
    MainWindow::choosePreview();
    setBpm->setIcon(QIcon(":/img/bpmuse.png"));
    editZt=6;
}

void MainWindow::choosePreview()
{
    setClick1->setIcon(QIcon(":/img/click1.png"));
    setClick2->setIcon(QIcon(":/img/click2.png"));
    setSlide->setIcon(QIcon(":/img/slid.png"));
    setPress1->setIcon(QIcon(":/img/press1.png"));
    setPress2->setIcon(QIcon(":/img/press2.png"));
    setBpm->setIcon(QIcon(":/img/bpm.png"));
    editZt=0;
}

void MainWindow::addNote()
{
    MainWindow::setCanSave();
    disconnect(tw,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(sorttw()));
    tww++;
    tw->setRowCount(tww);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,editZt-1);
    tw->setItem(tww-1,0,item);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,pressTime);
    tw->setItem(tww-1,1,item);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,pressPos);
    tw->setItem(tww-1,2,item);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,dNoteWidth);
    tw->setItem(tww-1,3,item);
    connect(tw,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(sorttw()));
    item=new QTableWidgetItem();
    if(editZt<=3)
        item->setData(Qt::DisplayRole,0);
    else if(editZt>=4)
        item->setData(Qt::DisplayRole,pressTime2-pressTime);
    tw->setItem(tww-1,4,item);
}

int MainWindow::searchPressNote(int a, int b, double p)
{
    int c=0,d=tww,e,f;
    double p1,p2;
    while(c<=d)
    {
        e=(c+d)/2;
        f=tw->item(e,1)->data(Qt::DisplayRole).toInt();
        if(f>=a-3&&f<b)
        {
            p1=tw->item(e,2)->data(Qt::DisplayRole).toDouble()-0.5*tw->item(e,3)->data(Qt::DisplayRole).toDouble();
            p2=tw->item(e,2)->data(Qt::DisplayRole).toDouble()+0.5*tw->item(e,3)->data(Qt::DisplayRole).toDouble();
            if(p>=p1&&p<=p2)
            {
                return e;
            }
            else if(p<p1)
            {
                d=e-1;
            }
            else if(p>p2)
            {
                c=e+1;
            }
        }
        else if(f>=b)
        {
            d=e-1;
        }
        else if(f<a-3)
        {
            c=e+1;
        }
    }
    return -1;
}

void MainWindow::deleteNote(int a)
{
    MainWindow::setCanSave();
    tw->removeRow(a);
    tww=tw->rowCount();
    paintzt=1;
    paintEvent(painte);
}

int MainWindow::searchBpm(int a)
{
//    qd()<<"start s bpm";
    int b=0;
    int c=bpmTable->rowCount()-1;
//    qd()<<"c"<<c;
    int d,e;
    int f=-999999;
    int g=0;//the bpm index
    while(b<=c)
    {
        d=(b+c)/2;
        e=bpmTable->item(d,0)->data(0).toInt();
        if(e>a)
        {
            c=d-1;
        }
        else if(e<=f)
        {
            b=d+1;
        }
        else if(e>f)
        {
            f=e;
            g=d;
            b=d+1;
//            qd()<<"g"<<g<<"b"<<b<<"c"<<c;
        }
    }
    return g;
}

void MainWindow::searchBpmIndex(int a)
{
    int index1,index0;
    double indexBpm,indexEffect;
    int indexTime,indexBeat,aBeat;
    index1=searchBpm(a);
    index0=index1;
//    qd()<<"index0"<<index0;
    indexTime=bpmTable->item(index1,0)->data(0).toInt();
    indexBpm=bpmTable->item(index1,1)->data(0).toDouble();
    indexEffect=bpmTable->item(index1,2)->data(0).toDouble();
    indexBeat=bpmTable->item(index1,3)->data(0).toInt();
    aBeat=indexBeat+(a-indexTime)/(1250/indexBpm);
//    qd()<<"abeat"<<aBeat;
    int m=labvis4;
    while(index1<bpmTable->rowCount()-1)
    {
//        qd()<<"+1-abeat"<<bpmTable->item(index1+1,3)->data(0).toInt()-aBeat;
        if((bpmTable->item(index1+1,3)->data(0).toInt()-aBeat)*smallbars/192.0*bh*indexEffect<=m)
        {
            m=m-(bpmTable->item(index1+1,3)->data(0).toInt()-aBeat)*smallbars/192.0*bh*indexEffect;
            index1++;
            aBeat=bpmTable->item(index1,3)->data(0).toInt();
            indexBpm=bpmTable->item(index1,1)->data(0).toDouble();
            indexEffect=bpmTable->item(index1,2)->data(0).toDouble();
        }
        else
            break;
    }
    //则有效bpm链为index0-index1
    paintBpmIndex1=index0;
    paintBpmIndex2=index1;
//    qd()<<paintBpmIndex1<<paintBpmIndex2;
    bpm=bpmTable->item(index0,1)->data(0).toDouble();
    dSlidValueTop=bpmTable->item(paintBpmIndex2,0)->data(0).toInt()+double(m)/double(bh*indexEffect)*double(1250/bpm);
}
