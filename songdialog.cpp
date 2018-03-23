#include "songdialog.h"

SongDialog::SongDialog()
{
    songInfoDialog=new QDialog();

    labTime=new QLabel(this);
    labTime->setGeometry(10,10,70,24);
    labTime->setText("歌曲时长");

    labSongName=new QLabel(this);
    labSongName->setGeometry(10,34,70,24);
    labSongName->setText("歌曲名");

    labInitBpm=new QLabel(this);
    labInitBpm->setGeometry(10,58,70,24);
    labInitBpm->setText("起始BPM");

    labArter=new QLabel(this);
    labArter->setGeometry(10,82,70,24);
    labArter->setText("作者");

    labNoter=new QLabel(this);
    labNoter->setGeometry(10,106,70,24);
    labNoter->setText("制作者");

    labOffset=new QLabel(this);
    labOffset->setGeometry(10,130,70,24);
    labOffset->setText("偏移量");

    labMusicFile=new QLabel(this);
    labMusicFile->setGeometry(10,154,70,24);
    labMusicFile->setText("音乐文件");

    textTime=new QLineEdit(this);
    textTime->setGeometry(80,10,150,24);
    textTime->setValidator(new QIntValidator(1000,36000000,this));

    textSongName=new QLineEdit(this);
    textSongName->setGeometry(80,34,150,24);

    textInitBpm=new QLineEdit(this);
    textInitBpm->setGeometry(80,58,150,24);
    textInitBpm->setValidator(new QDoubleValidator(0,99999999,5,this));

    textArter=new QLineEdit(this);
    textArter->setGeometry(80,82,150,24);

    textNoter=new QLineEdit(this);
    textNoter->setGeometry(80,106,150,24);

    textOffset=new QLineEdit(this);
    textOffset->setGeometry(80,130,150,24);

    textMusicFile=new QLineEdit(this);
    textMusicFile->setGeometry(80,154,150,24);

    ensure=new QPushButton(this);
    ensure->setGeometry(30,184,70,30);
    ensure->setText("确定");

    cancel=new QPushButton(this);
    cancel->setGeometry(140,184,70,30);
    cancel->setText("取消");
}

void SongDialog::setTime(int time)
{
    textTime->setText(QString("%1").arg(time));
}

void SongDialog::setSongName(QString songName)
{
    textSongName->setText(songName);
}

void SongDialog::setInitBpm(double initBpm)
{
    textInitBpm->setText(QString("%1").arg(initBpm));
}

void SongDialog::setArter(QString arter)
{
    textArter->setText(arter);
}

void SongDialog::setNoter(QString noter)
{
    textNoter->setText(noter);
}

void SongDialog::setOffset(int offset)
{
    textOffset->setText(QString("%1").arg(offset));
}

void SongDialog::setMusicFile(QString musicFile)
{
    textMusicFile->setText(musicFile);
}
