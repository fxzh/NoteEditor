#include <mainwindow.h>

void MainWindow::open()
{
    filedialog=new QFileDialog(this);
    filedialog->setAcceptMode(QFileDialog::AcceptOpen);
    filedialog->setWindowTitle(tr("打开"));
    QStringList list;
    list<<"Text files(*.txt)"<<"All files(*.*)";
    filedialog->setNameFilters(list);
    if(filedialog->exec()==QDialog::Rejected)
    {
        filedialog->close();
        delete filedialog;
    }
    else
    {
        path=filedialog->selectedFiles()[0];
        int cutleft=path.size();
        for(int i=path.size()-1;i>=0;i--)
        {
            if(path[i]=='/'||path[i]=='\\')
            {
                cutleft=i+1;
                break;
            }
        }
        pathab=path.left(cutleft);
        delete filedialog;
        filea=new QFile(path);
        loadToPaint(filea,path);
    }
}

void MainWindow::savethatfile()
{
    filedialog=new QFileDialog(this);
    filedialog->setAcceptMode(QFileDialog::AcceptSave);
    if(filedialog->exec()==QDialog::Rejected)
    {
        filedialog->close();
    }
    else
    {
        QString s=filedialog->selectedFiles()[0];
        writefile(s);
    }
    delete filedialog;
}

void MainWindow::loadfile(QFile * filea)
{
    if(!filea->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    QTextStream *fileb=new QTextStream(filea);
    version=fileb->readLine().toInt();
    PathMusic=fileb->readLine();
    musicName=PathMusic;    PathMusic.insert(0,pathab);     emit sendPathMusic(PathMusic);
    zongtime=fileb->readLine().toInt();
    name=fileb->readLine();
    arter=fileb->readLine();
    noter=fileb->readLine();
    offset=fileb->readLine().toInt();
    bpms=fileb->readLine().toInt();
    bpmTable=new QTableWidget(this);
    bpmTable->setVisible(false);
    bpmTable->setRowCount(bpms);
    bpmTable->setColumnCount(5);
    for(int i=0;i<bpms;i++)
    {
        int bpmtime=fileb->readLine().toInt();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,bpmtime);
        bpmTable->setItem(i,0,item);
        double onebpm=fileb->readLine().toDouble();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,onebpm);
        bpmTable->setItem(i,1,item);
        double bpmeffect=fileb->readLine().toDouble();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,bpmeffect);
        bpmTable->setItem(i,2,item);
        int bpmbeats=fileb->readLine().toInt();
        item=new QTableWidgetItem();
        item->setData(0,bpmbeats);
        bpmTable->setItem(i,3,item);
        int bpmcon=fileb->readLine().toInt();
        item=new QTableWidgetItem();
        item->setData(0,bpmcon);
        bpmTable->setItem(i,4,item);
    }
    bpm=bpmTable->item(0,1)->data(0).toDouble();
    effect=bpmTable->item(0,2)->data(0).toDouble();
    setSongDialog();
    cishu=fileb->readLine().toInt();
    tw=new QTableWidget(this);
    tww=cishu;
    twh=5;
    tw->setRowCount(cishu);//>>5
    tw->setColumnCount(5);//=5
    for(int i=0;i<tw->columnCount();i++)
        tw->setColumnWidth(i,70);
    twliew=5*tw->columnWidth(1)+55;//todebug    四位数足够
    QRect recttw(0,menuh+toolh,twliew,scrh-stah-70);
    tw->setGeometry(recttw);
    QStringList twhead;
    twhead<<"类型"<<"时间"<<"位置"<<"大小"<<"持续时间";
    tw->setHorizontalHeaderLabels(twhead);
    tw->show();
    for(int i=0;i<tw->rowCount();i++)
    {
        int notekind=fileb->readLine().toInt();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,notekind);
        tw->setItem(i,0,item);
        int notetime=fileb->readLine().toInt();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,notetime);
        tw->setItem(i,1,item);
        double notepos=fileb->readLine().toDouble();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,notepos);
        tw->setItem(i,2,item);
        double notesize=fileb->readLine().toDouble();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,notesize);
        tw->setItem(i,3,item);
        int noteextra=fileb->readLine().toInt();
        item=new QTableWidgetItem();
        item->setData(Qt::DisplayRole,noteextra);
        tw->setItem(i,4,item);
    }
    connect(tw,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(sorttw()));
    delete fileb;
}

void MainWindow::writefile(QString s)
{
    QFile *savingfile;
    savingfile=new QFile(s);
    savingfile->open(QFile::WriteOnly|QFile::Truncate);
    QTextStream *textsavefile=new QTextStream(savingfile);
    textsavefile->operator <<(version)<<endl<<(musicName)<<endl<<(zongtime)<<endl<<(name)<<endl<<(arter)<<endl\
                           <<(noter)<<endl<<(offset)<<endl<<(bpmTable->rowCount())<<endl;
    for(int i=0;i<bpmTable->rowCount();i++)
    {
        textsavefile->operator <<(bpmTable->item(i,0)->data(0).toInt())<<endl;
        textsavefile->operator <<(bpmTable->item(i,1)->data(0).toDouble())<<endl;
        textsavefile->operator <<(bpmTable->item(i,2)->data(0).toDouble())<<endl;
        textsavefile->operator <<(bpmTable->item(i,3)->data(0).toInt())<<endl;
        textsavefile->operator <<(bpmTable->item(i,4)->data(0).toInt())<<endl;
    }
    textsavefile->operator <<(tw->rowCount())<<endl;
    for(int i=0;i<tw->rowCount();i++)
    {
        textsavefile->operator <<(tw->item(i,0)->data(0).toInt())<<endl;
        textsavefile->operator <<(tw->item(i,1)->data(0).toInt())<<endl;
        textsavefile->operator <<(tw->item(i,2)->data(0).toDouble())<<endl;
        textsavefile->operator <<(tw->item(i,3)->data(0).toDouble())<<endl;
        textsavefile->operator <<(tw->item(i,4)->data(0).toInt())<<endl;
    }
    delete textsavefile;
    savingfile->close();
    delete savingfile;
}

void MainWindow::savefile()
{
    setNotSave();
    QString s=this->windowTitle();
    writefile(s);
}

void MainWindow::setCanSave()
{
    savefileaction->setEnabled(true);
    savefileaction->setIcon(QIcon(":/img/savefile.png"));
}

void MainWindow::setNotSave()
{
    savefileaction->setDisabled(true);
    savefileaction->setIcon(QIcon(":/img/cantsavefile.png"));
}

void MainWindow::closeFile()
{
    if(savefileaction->isEnabled()==true)
    {
        closeMessage.setWindowTitle("关闭");
        closeMessage.setText("是否保存并关闭文件");
        closeMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        closeMessage.setDefaultButton(QMessageBox::Yes);
        int ret=closeMessage.exec();
        if(ret==QMessageBox::Yes)
        {
            savefile();
            afterCloseFile();
        }
        else if(ret==QMessageBox::No)
        {
            afterCloseFile();
        }
    }
    else
    {
        afterCloseFile();
    }
}

void MainWindow::afterCloseFile()
{
    initPoint();
    setNotSave();
    firstOpen=1;
    PlayAction->setEnabled(false);
    songAction->setEnabled(false);
    closeFileAction->setEnabled(false);
    paintzt=0;
    setWindowTitle(versionString);
}

void MainWindow::checkSomeFiles()
{
    runPath = QCoreApplication::applicationDirPath();
    iniPath=QString("/editor.ini");
    iniPath.insert(0,runPath);
    QFileInfo iniInfo(iniPath);
    if(iniInfo.isFile()==false)
    {
        createAniniFile();
    }
    readAniniFile();
    sePixmapDir=QString("/sepixmap");
    sePixmapDir.insert(0,runPath);
    QDir se(sePixmapDir);
    if(se.exists()==false)
    {
        bool ok=se.mkdir(sePixmapDir);
        if(ok==false)
        {

        }
    }
    sePixmapPath=QString("/se.png");
    sePixmapPath.insert(0,sePixmapDir);
    QFileInfo seInfo(sePixmapPath);
    if(seInfo.isFile()==false)
    {
        createPngFile(0,244,251,sePixmapPath);
    }
    sePix=QPixmap(sePixmapPath);
}

void MainWindow::createPngFile(int r, int g, int b, QString path)
{
    QPixmap sePixmap(1,255);
    sePixmap.fill(Qt::transparent);
    QPainter sePen(&sePixmap);
    for(int i=255;i>0;i--)
    {
        sePen.setPen(QColor(r,g,b,i));
        sePen.drawPoint(0,i);
    }
    sePixmap.save(path);
}

void MainWindow::receiveNewData(QString songName, QString songAdd, QString initBpm, \
                                QString arter, QString noter, QString fileName, QString musicTime)
{
    int cutleft=songAdd.size();
    for(int i=songAdd.size()-1;i>=0;i--)
    {
        if(songAdd[i]=='/'||songAdd[i]=='\\')
        {
            cutleft=i;
            break;
        }
    }
    QString dir=songAdd.left(cutleft);
    QString songFile=songAdd.right(songAdd.size()-cutleft-1);
    QString txt=".txt";
    QString thefile=fileName+txt;
    QString puAdd=dir+"/"+thefile;
    QDir newdir;
    newdir.setCurrent(dir);
    QFile *tempFile = new QFile;
    if(tempFile->exists(thefile))
    {
        qDebug()<<"文件存在";
        return;
        //todo
    }
    else
    {
        tempFile->setFileName(thefile);
        if(tempFile->open(QFile::WriteOnly|QFile::Truncate))
        {
            QTextStream *textTempFile=new QTextStream(tempFile);
            textTempFile->operator <<("3")<<endl\
                                         <<(songFile)<<endl\
                                        <<(musicTime)<<endl\
                                       <<(songName)<<endl\
                                      <<(arter)<<endl\
                                     <<(noter)<<endl\
                                    <<("0")<<endl<<("1")<<endl\
                                   <<("0")<<endl<<(initBpm)<<endl<<("1")<<endl<<("0")<<endl<<("-1")<<endl<<("0");
            delete textTempFile;
            tempFile->close();
//            delete tempFile;
            loadToPaint(tempFile,puAdd);
        }
        else
        {
            qs<<"open failed";
        }
    }
}

void MainWindow::loadToPaint(QFile *a,QString path)
{
    if(firstOpen==0)
    {
        initPoint();
    }
    PlayAction->setEnabled(true);
    songAction->setEnabled(true);
    closeFileAction->setEnabled(true);
    firstOpen=0;
    paintzt=1;
    setWindowTitle(path);
    loadfile(a);
    initmid2();
    searchBpmIndex(0);
    beforepaint();
    paintEvent(painte);
}
