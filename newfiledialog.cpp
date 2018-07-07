#include "newfiledialog.h"

NewFileDialog::NewFileDialog()
{
    wid=new QWidget(this);
    wid->resize(400,250);
    grid=new QGridLayout(wid);
    grid->setColumnStretch(8,3);
    labSongName=new QLabel("歌曲名");
    labSongAdd=new QLabel("歌曲地址");
    labArter=new QLabel("作者");
    labInitBpm=new QLabel("初始BPM");
    labNoter=new QLabel("制作者");
    labFileName=new QLabel("谱面文件名");
    labMusicTime=new QLabel("音乐时长(ms)");
    editSongName=new QLineEdit();
    editSongAdd=new QLineEdit();
    editSongAdd->setReadOnly(true);
    bt=new QPushButton("浏览");
    connect(bt,SIGNAL(clicked(bool)),this,SLOT(selectMusicFile()));
    editArter=new QLineEdit();
    editInitBpm=new QLineEdit();
    editInitBpm->setValidator(new QDoubleValidator(0.0001,99999,4,this));
    editNoter=new QLineEdit();
    editFileName=new QLineEdit();
    editMusicTime=new QLineEdit();
    ensureButton=new QPushButton("确定");
    connect(ensureButton,SIGNAL(clicked(bool)),this,SLOT(checkComplete()));
    grid->addWidget(labSongName,0,0);
    grid->addWidget(editSongName,0,1,1,-1);
    grid->addWidget(labSongAdd,1,0);
    grid->addWidget(editSongAdd,1,1);
    grid->addWidget(bt,1,2);
    grid->addWidget(labArter,2,0);
    grid->addWidget(editArter,2,1,1,-1);
    grid->addWidget(labInitBpm,3,0);
    grid->addWidget(editInitBpm,3,1,1,-1);
    grid->addWidget(labNoter,4,0);
    grid->addWidget(editNoter,4,1,1,-1);
    grid->addWidget(labFileName,5,0);
    grid->addWidget(editFileName,5,1,1,-1);
    grid->addWidget(labMusicTime,6,0);
    grid->addWidget(editMusicTime,6,1,1,-1);
    grid->addWidget(ensureButton,7,1);
}

void NewFileDialog::selectMusicFile()
{
    newDialog=new QFileDialog(this);
    newDialog->setAcceptMode(QFileDialog::AcceptOpen);
    newDialog->setWindowTitle(tr("打开"));
    QStringList list;
    list<<"Music files(*.mp3 *.wav *.flac)"<<"All files(*.*)";
    newDialog->setNameFilters(list);
    if(newDialog->exec()==QDialog::Rejected)
    {
        newDialog->close();
        delete newDialog;
    }
    else
    {
        QString path=newDialog->selectedFiles()[0];
        delete newDialog;
        editSongAdd->setText(path);
    }
}

void NewFileDialog::checkComplete()
{
    if(editSongName->text().isEmpty()==false&&\
            editSongAdd->text().isEmpty()==false&&\
            editInitBpm->text().isEmpty()==false&&\
            editArter->text().isEmpty()==false&&\
            editNoter->text().isEmpty()==false&&\
            editFileName->text().isEmpty()==false&&\
            editMusicTime->text().isEmpty()==false)
    {
        emit sendData(editSongName->text(),editSongAdd->text(),editInitBpm->text(),\
                      editArter->text(),editNoter->text(),editFileName->text(),editMusicTime->text());
        this->close();
    }
    else
    {
        //todo
    }
}
