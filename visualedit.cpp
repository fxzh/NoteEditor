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
    setCanSave();
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
    setCanSave();
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

int MainWindow::searchBpmNote(int t)
{
    int p=0;
    int q=bpmTable->rowCount()-1;
    int r;
    while(p<=q)
    {
//        qs<<p<<q;
        r=(p+q)/2;
        if(bpmTable->item(r,0)->data(0).toInt()==t)
        {
            return r;
        }
        else if(bpmTable->item(r,0)->data(0).toInt()>t)
        {
            q=r-1;
        }
        else
        {
            p=r+1;
        }
    }
    return -1;
}

void MainWindow::addBpmNote()
{
    int r=bpmTable->rowCount();
    bpmTable->setRowCount(r+1);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,pressTime);
    bpmTable->setItem(r,0,item);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,editBpm->text().toDouble());
    bpmTable->setItem(r,1,item);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,editBpm2->text().toDouble());
    bpmTable->setItem(r,2,item);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,0);
    bpmTable->setItem(r,3,item);
    item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,0);
    bpmTable->setItem(r,4,item);
    bpmTable->sortByColumn(0,Qt::AscendingOrder);
/*    for(int i=0;i<bpmTable->rowCount();i++)
    {
        for(int j=0;j<5;j++)
        {
            qs<<bpmTable->item(i,j)->data(0);
        }
    }*/
    int index=searchBpmNote(pressTime);
    if(index!=-1)
    {
        changeBpmNote(index);
    }
    else
    {
        qs<<"error";
    }
}

void MainWindow::changeBpmNote(int index)
{
    setCanSave();
    item=bpmTable->item(index,0);
    item->setData(Qt::DisplayRole,pressTime);
    item=bpmTable->item(index,1);
    item->setData(Qt::DisplayRole,editBpm->text().toDouble());
    item=bpmTable->item(index,2);
    item->setData(Qt::DisplayRole,editBpm2->text().toDouble());
    item=bpmTable->item(index,3);
    item->setData(Qt::DisplayRole,0);
    item=bpmTable->item(index,4);
    item->setData(Qt::DisplayRole,0);

    double b0=bpmTable->item(index,0)->data(0).toDouble();
    double b1=bpmTable->item(index,1)->data(0).toDouble();
    double b3=bpmTable->item(index,3)->data(0).toDouble();
    if(index!=0)
    {
        double a0=bpmTable->item(index-1,0)->data(0).toDouble();
        double a1=bpmTable->item(index-1,1)->data(0).toDouble();
        double a3=bpmTable->item(index-1,3)->data(0).toDouble();
        double x=(b0-a0)*a1/1250.0;
        item=bpmTable->item(index-1,4);
        item->setData(Qt::DisplayRole,x);
        item=bpmTable->item(index,3);
        item->setData(Qt::DisplayRole,a3+x);
    }
    else
    {
        item=bpmTable->item(index,3);
        item->setData(Qt::DisplayRole,0);
    }
    if(index!=bpmTable->rowCount()-1)
    {
        double c0=bpmTable->item(index+1,0)->data(0).toDouble();
        double c3=bpmTable->item(index+1,3)->data(0).toDouble();
        double y=(c0-b0)*18/b1;
        item=bpmTable->item(index,4);
        item->setData(Qt::DisplayRole,y);
        double cha=b3+y-c3;
        for(int i=index+1;i<bpmTable->rowCount()-1;i++)
        {
            item=bpmTable->item(i,3);
            double i3=item->data(0).toDouble();
            item->setData(Qt::DisplayRole,i3+cha);
        }
    }
    else
    {
        item=bpmTable->item(index,4);
        item->setData(Qt::DisplayRole,-1);
    }
}

int MainWindow::searchBpmNote2(int a, int b)
{
    int p=0;
    int q=bpmTable->rowCount();
    int r;
    while(p<=q)
    {
        r=(p+q)/2;
        int t=bpmTable->item(r,0)->data(0).toInt();
        if(t<a)
        {
            p=r+1;
        }
        else if(t>=b)
        {
            q=r-1;
        }
        else if(r!=0)
        {
            return r;
        }
    }
    return -1;
}

void MainWindow::deleteBpmNote(int index)
{
    setCanSave();
    if(index==bpmTable->rowCount()-1)
    {
        item=bpmTable->item(index-1,4);
        item->setData(Qt::DisplayRole,-1);
    }
    else
    {
        double a0=bpmTable->item(index-1,0)->data(0).toDouble();
        double a1=bpmTable->item(index-1,1)->data(0).toDouble();
        double a3=bpmTable->item(index-1,3)->data(0).toDouble();
        double c0=bpmTable->item(index+1,0)->data(0).toDouble();
        double c3=bpmTable->item(index+1,3)->data(0).toDouble();
        double x=(c0-a0)*a1/1250.0;
        item=bpmTable->item(index-1,4);
        item->setData(0,x);
        double cha=a3+x-c3;
        for(int i=index+1;i<bpmTable->rowCount()-1;i++)
        {
            item=bpmTable->item(i,3);
            double i3=item->data(0).toDouble();
            item->setData(0,i3+cha);
        }
    }
    bpmTable->removeRow(index);
}
