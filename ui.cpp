#include <mainwindow.h>

void MainWindow::initmid()
{
    labeltime1=twliew;
    labeltime2=menuh+toolh+10;
    labeltime3=70;
    labeltime4=24;

    texttime1=labeltime1+labeltime3;
    texttime2=labeltime2;
    texttime3=70;
    texttime4=24;

    labsb1=labeltime1;
    labsb2=labeltime2;
    labsb3=labeltime3;
    labsb4=labeltime4;

    sbsb1=labsb1+labsb3;
    sbsb2=labsb2;
    sbsb3=labeltime3;
    sbsb4=labeltime4;

    labbarheight1=labeltime1;
    labbarheight2=labsb2+labsb4;
    labbarheight3=labeltime3;
    labbarheight4=labeltime4;

    sbbarheight1=labbarheight1+labbarheight3;
    sbbarheight2=labbarheight2;
    sbbarheight3=labeltime3;
    sbbarheight4=labeltime4;

    LabWhellDistance1=labeltime1;
    LabWhellDistance2=labbarheight2+labbarheight4;
    LabWhellDistance3=labeltime3;
    LabWhellDistance4=labeltime4;

    CbWhellDistance1=LabWhellDistance1+LabWhellDistance3;
    CbWhellDistance2=LabWhellDistance2;
    CbWhellDistance3=labeltime3;
    CbWhellDistance4=labeltime4;

    labNoteWidth1=labeltime1;
    labNoteWidth2=LabWhellDistance2+LabWhellDistance4;
    labNoteWidth3=labeltime3;
    labNoteWidth4=labeltime4;

    editNoteWidth1=labeltime1+labeltime3;
    editNoteWidth2=labNoteWidth2;
    editNoteWidth3=labeltime3;
    editNoteWidth4=labeltime4;

    slid1=scrw-50;
    slid2=labeltime2;
    slid3=25;
    slid4=scrh-slid2-50;

    labvis1=texttime1+texttime3+50;
    labvis2=menuh+toolh;
    labvis3=scrw-labvis1-slid3-30;
    labvis4=scrh-stah-labvis2-20;
}

void MainWindow::paintmid()
{
    QRect relabsb(labsb1,labsb2,labsb3,labsb4);
    QRect resbsb(sbsb1,sbsb2,sbsb3,sbsb4);
    QRect relabbarheight(labbarheight1,labbarheight2,labbarheight3,labbarheight4);
    QRect resbbarheight(sbbarheight1,sbbarheight2,sbbarheight3,sbbarheight4);
    QRect ReLabWhell(LabWhellDistance1,LabWhellDistance2,LabWhellDistance3,LabWhellDistance4);
    QRect ReCbWhell(CbWhellDistance1,CbWhellDistance2,CbWhellDistance3,CbWhellDistance4);
    QRect reLabNoteWidth(labNoteWidth1,labNoteWidth2,labNoteWidth3,labNoteWidth4);
    QRect reEditNoteWidth(editNoteWidth1,editNoteWidth2,editNoteWidth3,editNoteWidth4);
    QRect reslid(slid1,slid2,slid3,slid4);
    QRect relabvis(labvis1,labvis2,labvis3,labvis4);

    labsb=new QLabel(this);
    labsb->setGeometry(relabsb);
    labsb->setAlignment(Qt::AlignCenter);
    labsb->setText(QString("小节数"));
    labsb->show();

    smallbar=new QComboBox(this);
    smallbar->setGeometry(resbsb);
    QStringList sblist;
    sblist<<"1"<<"2"<<"3"<<"4"<<"6"<<"8"<<"12"<<"16"<<"24"<<"32"<<"48"<<"64";
    smallbar->addItems(sblist);
    smallbar->setCurrentIndex(smallbarIndex);
    smallbar->show();
    connect(smallbar,SIGNAL(currentTextChanged(QString)),this,SLOT(changesb()));

    labbh=new QLabel(this);
    labbh->setGeometry(relabbarheight);
    labbh->setAlignment(Qt::AlignCenter);
    labbh->setText(QString("小节高"));
    labbh->show();

    barheight=new QSpinBox(this);
    barheight->setGeometry(resbbarheight);
    barheight->setRange(10,1000);
    barheight->setSuffix(QString("像素"));
    barheight->setValue(smallbarPx);
    bh=smallbarPx;
    barheight->show();
    connect(barheight,SIGNAL(valueChanged(int)),this,SLOT(changebh(int)));

    LabWhellDistance=new QLabel(this);
    LabWhellDistance->setGeometry(ReLabWhell);
    LabWhellDistance->setAlignment(Qt::AlignCenter);
    LabWhellDistance->setText(QString("滚轮距离"));
    LabWhellDistance->show();

    WhellDistance=new QComboBox(this);
    WhellDistance->setGeometry(ReCbWhell);
    QStringList wdlist;
    wdlist<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8";
    WhellDistance->addItems(wdlist);
    WhellDistance->setCurrentIndex(wheelIndex);
    WhellDistance->show();
    connect(WhellDistance,SIGNAL(currentTextChanged(QString)),this,SLOT(changeWh()));

    labNoteWidth=new QLabel(this);
    labNoteWidth->setGeometry(reLabNoteWidth);
    labNoteWidth->setAlignment(Qt::AlignCenter);
    labNoteWidth->setText(QString("键宽"));
    labNoteWidth->show();

    editNoteWidth=new QDoubleSpinBox(this);
    editNoteWidth->setGeometry(reEditNoteWidth);
    editNoteWidth->setRange(0.05,5);
    editNoteWidth->setSingleStep(editNoteStep);
    editNoteWidth->setValue(dNoteWidth);
    editNoteWidth->show();
    connect(editNoteWidth,SIGNAL(valueChanged(double)),this,SLOT(changeNoteWidth(double)));

    slid=new QSlider(this);
    slid->setGeometry(reslid);
    slid->setMinimum(0);
    slid->setMaximum(zongtime);
    slid->show();
    connect(slid,SIGNAL(valueChanged(int)),this,SLOT(changeslid(int)));

    labvis=new QLabel(this);
    labvis->setGeometry(relabvis);
    labvis->setMouseTracking(true);
    labvis->show();

    whd=240000/bpm/smallbars;
}

void MainWindow::setSongDialog()
{
    editSongDialog=new SongDialog();
    editSongDialog->setWindowTitle("编辑谱面信息");
    editSongDialog->setTime(zongtime);
    editSongDialog->setSongName(name);
    editSongDialog->setInitBpm(bpmTable->item(0,1)->data(0).toDouble());
    editSongDialog->setArter(arter);
    editSongDialog->setNoter(noter);
    editSongDialog->setOffset(offset);
    editSongDialog->setMusicFile(musicName);
    connect(editSongDialog->ensure,SIGNAL(clicked(bool)),this,SLOT(ensureButton()));
    connect(editSongDialog->cancel,SIGNAL(clicked(bool)),this,SLOT(cancelButton()));
}

void MainWindow::initPoint()
{
    delete th2->MusicMp3;
    delete slid;
    delete tw;
    delete labsb;
    delete labbh;
    delete LabWhellDistance;
    delete labNoteWidth;
    delete labvis;
    delete smallbar;
    delete WhellDistance;
    delete barheight;
    delete editNoteWidth;
    delete editSongDialog;
}
