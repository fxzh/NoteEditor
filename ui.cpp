#include <mainwindow.h>

void MainWindow::initmid2()
{
    midWidget=new QWidget(this);
    midWidget->setGeometry(QRect(twliew,menuh+toolh,180,180));
    midLayout=new QGridLayout(midWidget);
    midLayout->setColumnStretch(2,6);
    labsb=new QLabel("小节数");

    smallbar=new QComboBox();
    QStringList sblist;
    sblist<<"1"<<"2"<<"3"<<"4"<<"6"<<"8"<<"12"<<"16"<<"24"<<"32"<<"48"<<"64";
    smallbar->addItems(sblist);
    smallbar->setCurrentIndex(smallbarIndex);
    connect(smallbar,SIGNAL(currentTextChanged(QString)),this,SLOT(changesb()));

    labbh=new QLabel("小节高");

    barheight=new QSpinBox();
    barheight->setRange(10,1000);
    barheight->setSuffix(QString("像素"));
    barheight->setValue(smallbarPx);
    bh=smallbarPx;
    connect(barheight,SIGNAL(valueChanged(int)),this,SLOT(changebh(int)));

    LabWhellDistance=new QLabel("滚轮距离");

    WhellDistance=new QComboBox(this);
    QStringList wdlist;
    wdlist<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8";
    WhellDistance->addItems(wdlist);
    WhellDistance->setCurrentIndex(wheelIndex);
    connect(WhellDistance,SIGNAL(currentTextChanged(QString)),this,SLOT(changeWh()));

    labNoteWidth=new QLabel("键宽");

    editNoteWidth=new QDoubleSpinBox();
    editNoteWidth->setRange(0.05,5);
    editNoteWidth->setSingleStep(editNoteStep);
    editNoteWidth->setValue(dNoteWidth);
    connect(editNoteWidth,SIGNAL(valueChanged(double)),this,SLOT(changeNoteWidth(double)));

    labBpm=new QLabel("变速BPM");

    editBpm=new QLineEdit(QString("100"));
    editBpm->setValidator(new QDoubleValidator(0.001,10000,4,this));

    labBpm2=new QLabel("缩放");

    editBpm2=new QLineEdit(QString("1"));
    editBpm2->setValidator(new QDoubleValidator(0.001,100,4,this));

    midLayout->addWidget(labsb,0,0);
    midLayout->addWidget(smallbar,0,1);
    midLayout->addWidget(labbh,1,0);
    midLayout->addWidget(barheight,1,1);
    midLayout->addWidget(LabWhellDistance,2,0);
    midLayout->addWidget(WhellDistance,2,1);
    midLayout->addWidget(labNoteWidth,3,0);
    midLayout->addWidget(editNoteWidth,3,1);
    midLayout->addWidget(labBpm,4,0);
    midLayout->addWidget(editBpm,4,1);
    midLayout->addWidget(labBpm2,5,0);
    midLayout->addWidget(editBpm2,5,1);
    midWidget->show();


    slid1=scrw-50;
    slid2=menuh+toolh+10;
    slid3=25;
    slid4=scrh-slid2-50;

    labvis1=twliew+190;
    labvis2=menuh+toolh;
    labvis3=scrw-labvis1-slid3-30;
    labvis4=scrh-stah-labvis2-20;

    QRect reslid(slid1,slid2,slid3,slid4);
    QRect relabvis(labvis1,labvis2,labvis3,labvis4);

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
    delete labBpm;
    delete labBpm2;
    delete editBpm;
    delete editBpm2;
    delete midWidget;
}
