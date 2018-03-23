#ifndef SONGDIALOG_H
#define SONGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QDoubleValidator>

class SongDialog : public QDialog
{
    Q_OBJECT
public:
    QDialog *songInfoDialog;
    QLabel *labTime,*labSongName,*labInitBpm,*labArter,*labNoter,*labOffset,*labMusicFile;
    QLineEdit *textTime,*textSongName,*textInitBpm,*textArter,*textNoter,*textOffset,*textMusicFile;
    QPushButton *ensure,*cancel;
    SongDialog();
    void setTime(int time);
    void setSongName(QString songName);
    void setInitBpm(double initBpm);
    void setArter(QString arter);
    void setNoter(QString noter);
    void setOffset(int offset);
    void setMusicFile(QString musicFile);
    int songTime()const
    {
        return textTime->text().toInt();
    }
    QString songName()const
    {
        return textSongName->text();
    }
    double initBpm()const
    {
        return textInitBpm->text().toDouble();
    }
    QString arter()const
    {
        return textArter->text();
    }
    QString noter()const
    {
        return textNoter->text();
    }
    int offset()const
    {
        return textOffset->text().toInt();
    }
    QString musicFile()const
    {
        return textMusicFile->text();
    }
};

#endif // SONGDIALOG_H
