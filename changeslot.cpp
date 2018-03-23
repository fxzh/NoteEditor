#include <mainwindow.h>

void MainWindow::sorttw()
{
    tw->sortByColumn(2,Qt::AscendingOrder);
    tw->sortItems(1,Qt::AscendingOrder);
}

void MainWindow::changesb()
{
    int csmallbars=smallbar->currentText().toInt();
    smallbars=csmallbars;
    MainWindow::changeWh();
    MainWindow::beforepaint();
    paintzt=1;
}

void MainWindow::changebh(int a)
{
    bh=a;
    MainWindow::beforepaint();
    paintzt=1;
}

void MainWindow::changeslid(int a)
{
    slidvalue=a;
    MainWindow::searchBpmIndex(a);
    MainWindow::beforepaint();
    paintzt=1;
}

void MainWindow::changeWh()
{
    int cwhd=WhellDistance->currentText().toInt();
    whd=cwhd*240000/bpm/smallbars;
}

void MainWindow::changeNoteWidth(double a)
{
    dNoteWidth=a;
}

void MainWindow::forTh3Update(int a)
{
    slid->setValue(a);
    MainWindow::musicBeforePaint();
}

void MainWindow::editSongInfo()
{
    editSongDialog->show();
}

void MainWindow::editSetting()
{
    setInit->show();
}

void MainWindow::ensureButton()
{
    int flag=0;
    int needPaint=0;
    if(name!=editSongDialog->songName())
    {
        name=editSongDialog->songName();
        flag=1;
    }
    if(zongtime!=editSongDialog->songTime())
    {
        zongtime=editSongDialog->songTime();
        slid->setMaximum(zongtime);
        flag=1;
        needPaint=1;
    }
    if(bpmTable->item(0,1)->data(0).toDouble()!=editSongDialog->initBpm())
    {
        bpmTable->item(0,1)->setData(0,editSongDialog->initBpm());
        bpm=editSongDialog->initBpm();
        MainWindow::changeWh();
        flag=1;
        needPaint=1;
    }
    if(arter!=editSongDialog->arter())
    {
        arter=editSongDialog->arter();
        flag=1;
    }
    if(noter!=editSongDialog->noter())
    {
        noter=editSongDialog->noter();
        flag=1;
    }
    if(offset!=editSongDialog->offset())
    {
        offset=editSongDialog->offset();
        flag=1;
        needPaint=1;
    }
    if(flag==1)
    {
        MainWindow::setCanSave();
    }
    if(needPaint==1)
    {
        MainWindow::musicBeforePaint();
    }
    editSongDialog->close();
}

void MainWindow::cancelButton()
{
    editSongDialog->close();
}

void MainWindow::settingEnsureButton()
{
    MainWindow::writeAniniFile();
    setInit->close();
}

void MainWindow::settingCancelButton()
{
    setInit->close();
}
