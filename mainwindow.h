#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QComboBox>
#include <QSpinBox>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDialog>
#include <QDebug>
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QCloseEvent>
#include <QList>
#include <QChar>
#include <QMediaPlayer>
#include <QPoint>
#include <QSettings>
#include <QTime>
#include <secthread.h>
#include <timethread.h>
#include <songdialog.h>
#include <settingdialog.h>
#define qd qDebug

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct note
    {
        int kind;       //0:单点  1：不用点的单点    2：滑     3：按     4：不用点的按
        int ntime;
        double weizhi;
        double daxiao;
        int can;
    };
    int scrh;//屏幕高
    int scrw;//屏幕宽
    int menuh;//菜单栏高
    int toolh;//工具按钮高
    int stah;//底部状态栏高
//    note anote[10000];
    int cishu;
    int zongtime;
    double bpm;int bpms;
    double effect;
    int offset;

    QTableWidget *tw,*bpmTable;
    QFile *filea;
    QAction *openAction,*newfileaction,*savefileaction,*savethatfileaction,*PlayAction,*aboutAction,\
            *setClick1,*setClick2,*setPress1,*setPress2,*setSlide,*setPreview,*closeFileAction,*songAction,\
            *settingAction,*setBpm;
    QFileDialog *filedialog;
    QDesktopWidget *deskw;
    QLabel *labeltime,*labsb,*labbh,*LabWhellDistance,*labNoteWidth,*labvis;
    QString name,arter,noter,path,pathab,PathMusic,musicName,runPath,iniPath,sePixmapDir,sePixmapPath;
    QComboBox *smallbar,*WhellDistance;
    QMessageBox aboutMessage,closeMessage;
    QSettings *iniSettings;
    QSpinBox *barheight;
    QDoubleSpinBox *editNoteWidth;
    QSlider *slid;
    QTime testTime;int times=0;

    QPaintEvent *painte;
    QMouseEvent *mousee;
    QCloseEvent *closee;
    secthread *th2;
    timethread *th3;
    SongDialog *editSongDialog;
    SettingDialog *setInit;

    int smallbars=16;               //小节数
    int bh=50;                      //每小节像素高
    int whd;                        //滚轮距离
    int paintcishu=0;
    int slidvalue=0;
    int slid1,slid2,slid3,slid4;
    QPixmap pix,sePix,seScaredPix;
    int pix1,pix2;
    int version;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    int twh,tww;//twh：表格列=5     twh：表格行
    int twliew;//最左列宽
    int texttime1,texttime2,texttime3,texttime4;
    int labeltime1,labeltime2,labeltime3,labeltime4;
    int labsb1,labsb2,labsb3,labsb4;
    int sbsb1,sbsb2,sbsb3,sbsb4;
    int labbarheight1,labbarheight2,labbarheight3,labbarheight4;
    int sbbarheight1,sbbarheight2,sbbarheight3,sbbarheight4;
    int labvis1,labvis2,labvis3,labvis4;
    int scrvis1,scrvis2,scrvis3,scrvis4;
    int LabWhellDistance1,LabWhellDistance2,LabWhellDistance3,LabWhellDistance4;
    int CbWhellDistance1,CbWhellDistance2,CbWhellDistance3,CbWhellDistance4;
    int labNoteWidth1,labNoteWidth2,labNoteWidth3,labNoteWidth4;
    int editNoteWidth1,editNoteWidth2,editNoteWidth3,editNoteWidth4;
    int paintzt=0;//0:没有文件打开/1：需要重绘/2：不需要重绘
    double dZtime;                  //  dZtime=zongtime;
    double dBigbarTime;             //  dBigbarTime=240000/bpm;
    int BigbarTime;                 //  BigbarTime=dBigbarTime;
    double dSmallbarTime;           //  dSmallbarTime=240000/bpm/smallbars;
    int SmallbarTime;               //  SmallbarTime=dSmallbarTime;
    double dFirstSmallbarTime;      //  dFirstSmallbarTime=dSmallbarTime*int(dZtime/dSmallbarTime+1);
    int FirstSmallbarTime;          //  FirstSmallbarTime=dFirstSmallbarTime;
    double dFirstSmallpx;           //  dFirstSmallpx=bh/dSmallbarTime*(dFirstSmallbarTime-slidvalue);
    int FirstSmallpx;               //  FirstSmallpx=dFirstSmallpx;
    double dFirstBigbarTime;        //  dFirstBigbarTime=dBigbarTime*int(dZtime/dBigbarTime+1);
    int FirstBigbarTime;            //  FirstBigbarTime=dFirstBigbarTime;
    double dFirstBigpx;             //  dFirstBigpx=bh/dSmallbarTime*(dFirstBigbarTime-slidvalue);
    int FirstBigpx;                 //  FirstBigpx=dFirstBigpx;
    double dLastSmallbarTime;       //  dLastSmallbarTime=dFirstSmallbarTime+labvis4*dSmallbarTime/bh;
    double dMidbarTime;         int midbarTime;
    double dFirstMidpx;         int firstMidpx;
    double dFirstMidbarTime;    int firstMidbarTime;
    int LastSmallbarTime;
    double dSlidValueTop;           //  dSlidValueTop=slid->value()+labvis4*dSmallbarTime/bh;
    int SlidValueTop;
    int MouseInLabvis=0;
    int playZt=-1;
    int editZt=0;
    int labMouseX,labMouseY;
    double dNoteWidth;
    QPoint editPoint1,editPoint2,editPoint3,editPoint4;
    int pressTime,pressTime2,moveTime2,moveLongNotePx;
    double pressPos;
    int longEditZt=0;
    int delPressTime1,delPressTime2;
    int firstOpen=1;
    QTableWidgetItem *item;
    int screenX,screenY;
    int wheelDirection,wheelIndex;
    double editNoteStep;
    int videoDelay;
    int smallbarIndex,smallbarPx;
    int paintBpmIndex1,paintBpmIndex2;
    double dBpmConPx;int bpmConPx;
    double dFirstNonePx;int firstNonePx;
    double dBpmLastTime;int bpmLastTime;
public slots:
    void open();
    void newfile();
    void savefile();
    void savethatfile();
    void sorttw();
    void changesb();
    void changebh(int a);
    void changeslid(int a);
    void changeWh();
    void PlayMusic();
    void changeSlidForMusic();
    void forTh3Update(int a);
    void showAbout();
    void chooseClick1();
    void chooseClick2();
    void chooseSlid();
    void choosePress1();
    void choosePress2();
    void choosePreview();
    void chooseBpm();
    void changeNoteWidth(double a);
    void closeFile();
    void editSongInfo();
    void editSetting();
    void ensureButton();
    void cancelButton();
    void settingEnsureButton();
    void settingCancelButton();
signals:
    void sendPaintZt(int);
    void sendPathMusic(QString);
    void sendPlayZt(int,int);
    void sendVideoDelay(int);
    void sendBeginTime(int);
    void sendTh3Exit();
    void sendTh2GetMusic();
    void th3ExitLoop();
public:
    void loadfile(QFile *filea);
    void writefile(QString s);
    void initmid();
    void paintmid();
    void beforepaint();
    void musicBeforePaint();
    void mainWindowMenuBar();
    void editBeforePaint();
    void addNote();
    void deleteNote(int a);
    int searchPressNote(int a,int b,double p);
    void initPoint();
    void setCanSave();
    void setNotSave();
    void createAniniFile();
    void readAniniFile();
    void writeAniniFile();
    void setSongDialog();
    void writeSetting();
    void checkSomeFiles();
    void createPngFile(int r,int g,int b,QString path);
    int searchBpm(int a);
    void searchBpmIndex(int a);
    int inPaint(int bpmtime, double bpm, double bpmeffect, int bpmbeats, int bpmcon, int bpmnonepx);
protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *rese);
    void mousePressEvent(QMouseEvent *pe);
    void wheelEvent(QWheelEvent *we);
    void mouseMoveEvent(QMouseEvent *me);
    void closeEvent(QCloseEvent *ce);
};

#endif // MAINWINDOW_H
