#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QDebug>
#define qs qDebug()

class NewFileDialog : public QDialog
{
    Q_OBJECT
public:
    QWidget *wid;
    QGridLayout *grid;
    QPushButton *bt,*ensureButton;
    QLabel *labSongName,*labInitBpm,*labArter,*labNoter,*labSongAdd,*labFileName,*labMusicTime;
    QLineEdit *editSongName,*editInitBpm,*editArter,*editNoter,*editSongAdd,*editFileName,*editMusicTime;
    QFileDialog *newDialog;
public:
    NewFileDialog();
signals:
    void sendData(QString songName,QString songAdd,QString initBpm,\
                  QString arter,QString noter,QString fileName,QString musicTime);
public slots:
    void selectMusicFile();
    void checkComplete();
};

#endif // NEWFILEDIALOG_H
