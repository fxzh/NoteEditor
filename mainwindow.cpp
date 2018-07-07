#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    deskw=new QDesktopWidget();
    deskw=QApplication::desktop();
    QRect deskrect=deskw->availableGeometry();    
    scrw=deskrect.width();
    scrh=deskrect.height();

    th2=new secthread();
    connect(this,SIGNAL(sendPaintZt(int)),th2,SLOT(setPaintZt(int)));
    connect(this,SIGNAL(sendPathMusic(QString)),th2,SLOT(setPathMusic(QString)));
    connect(this,SIGNAL(sendPlayZt(int,int)),th2,SLOT(setPlayZt(int,int)));
    connect(th2,SIGNAL(sendMainMusic(int)),this,SLOT(forTh3Update(int)));

    th3=new timethread();
    connect(this,SIGNAL(sendBeginTime(int)),th3,SLOT(beginTime(int)));
    connect(this,SIGNAL(sendTh3Exit()),th3,SLOT(exitTh3()));
    connect(th3,SIGNAL(getMusicPosition()),th2,SLOT(getMusic()));
    connect(this,SIGNAL(sendVideoDelay(int)),th3,SLOT(getVideoDelay(int)));
    connect(this,SIGNAL(th3ExitLoop()),th3,SLOT(exitWhile()));

    MainWindow::checkSomeFiles();

    setWindowTitle(tr("Note Editor 0.9.1"));
    resize(screenX,screenY);
    screenY=this->height();
    screenX=this->width();

    MainWindow::mainWindowMenuBar();

    this->setMouseTracking(true);
}

void MainWindow::mainWindowMenuBar()
{
    openAction=new QAction(QIcon(":/img/open.png"),"&打开...",this);
    openAction->setShortcut(tr("ctrl+o"));
    openAction->setStatusTip(tr("打开一个文件"));
    connect(openAction,&QAction::triggered,this,&MainWindow::open);

    newfileaction=new QAction(QIcon(":/img/newfile.png"),"&新建...",this);
    newfileaction->setShortcut(tr("ctrl+n"));
    newfileaction->setStatusTip(tr("新建一个文件"));
    connect(newfileaction,&QAction::triggered,this,&MainWindow::newfile);

    newfileaction->setDisabled(true);//To Delete

    savefileaction=new QAction(QIcon(":/img/cantsavefile.png"),"&保存...",this);
    savefileaction->setShortcut(tr("ctrl+s"));
    savefileaction->setStatusTip(tr("保存文件"));
    savefileaction->setDisabled(true);
    connect(savefileaction,&QAction::triggered,this,&MainWindow::savefile);

    savethatfileaction=new QAction("&另存为...",this);
    savethatfileaction->setShortcut(tr("ctrl+alt+s"));
    savethatfileaction->setStatusTip(tr("将文件存储至另一个位置"));
    connect(savethatfileaction,SIGNAL(triggered(bool)),this,SLOT(savethatfile()));

    closeFileAction=new QAction(QIcon(":/img/closefile.png"),"关闭...",this);
    closeFileAction->setShortcut(tr("ctrl+w"));
    closeFileAction->setStatusTip(tr("关闭文件"));
    connect(closeFileAction,SIGNAL(triggered(bool)),this,SLOT(closeFile()));

    closeFileAction->setDisabled(true);//To Delete

    songAction=new QAction("编辑谱面信息",this);
    songAction->setDisabled(true);
    connect(songAction,SIGNAL(triggered(bool)),this,SLOT(editSongInfo()));

    settingAction=new QAction("设置",this);
    connect(settingAction,SIGNAL(triggered(bool)),this,SLOT(editSetting()));

    PlayAction=new QAction(QIcon(":/img/play.png"),"播放/暂停",this);
    PlayAction->setShortcut(tr("alt+."));
    PlayAction->setStatusTip(tr("播放/暂停音乐"));
    PlayAction->setDisabled(true);
    connect(PlayAction,SIGNAL(triggered(bool)),this,SLOT(PlayMusic()));

    aboutAction=new QAction("关于...",this);
    connect(aboutAction,SIGNAL(triggered(bool)),this,SLOT(showAbout()));

    setClick1=new QAction(QIcon(":/img/click1.png"),"Click1",this);
    setClick1->setShortcut(tr("q"));
    setClick1->setStatusTip(tr("画蓝色单点"));
    connect(setClick1,SIGNAL(triggered(bool)),this,SLOT(chooseClick1()));

    setClick2=new QAction(QIcon(":/img/click2.png"),"Click2",this);
    setClick2->setShortcut(tr("w"));
    setClick2->setStatusTip(tr("画橙色单点"));
    connect(setClick2,SIGNAL(triggered(bool)),this,SLOT(chooseClick2()));

    setSlide=new QAction(QIcon(":/img/slid.png"),"Slid",this);
    setSlide->setShortcut(tr("e"));
    setSlide->setStatusTip(tr("画紫色滑键"));
    connect(setSlide,SIGNAL(triggered(bool)),this,SLOT(chooseSlid()));

    setPress1=new QAction(QIcon(":/img/press1.png"),"Press1",this);
    setPress1->setShortcut(tr("a"));
    setPress1->setStatusTip(tr("画绿色长键"));
    connect(setPress1,SIGNAL(triggered(bool)),this,SLOT(choosePress1()));

    setPress2=new QAction(QIcon(":/img/press2.png"),"Press2",this);
    setPress2->setShortcut(tr("s"));
    setPress2->setStatusTip(tr("画黄色长键"));
    connect(setPress2,SIGNAL(triggered(bool)),this,SLOT(choosePress2()));

    setBpm=new QAction(QIcon(":/img/bpm.png"),"设置BPM",this);
    setBpm->setStatusTip(tr("设置变速BPM的起始点"));
    connect(setBpm,SIGNAL(triggered(bool)),this,SLOT(chooseBpm()));

    setPreview=new QAction(QIcon(":/img/preview.png"),"预览",this);
    setPreview->setShortcut(tr("d"));
    setPreview->setStatusTip(tr("进行预览"));
    connect(setPreview,SIGNAL(triggered(bool)),this,SLOT(choosePreview()));

    QMenu *menu=menuBar()->addMenu("&文件");
    menu->addAction(newfileaction);
    menu->addAction(openAction);
    menu->addAction(savefileaction);
    menu->addAction(savethatfileaction);
    menu->addAction(closeFileAction);

    QMenu *menuEdit=menuBar()->addMenu("编辑");
    menuEdit->addAction(songAction);
    menuEdit->addAction(settingAction);

    QMenu *menu2=menuBar()->addMenu("播放");
    menu2->addAction(PlayAction);

    QMenu *menu3=menuBar()->addMenu("帮助");
    menu3->addAction(aboutAction);

    QToolBar *toolBar=addToolBar(tr("&Filetool"));
    toolBar->addAction(newfileaction);
    toolBar->addAction(openAction);
    toolBar->addAction(savefileaction);
    toolBar->addAction(closeFileAction);
    toolBar->addAction(PlayAction);
    toolBar->addAction(setClick1);
    toolBar->addAction(setClick2);
    toolBar->addAction(setSlide);
    toolBar->addAction(setPress1);
    toolBar->addAction(setPress2);
    toolBar->addAction(setBpm);
    toolBar->addAction(setPreview);

    QStatusBar*status=statusBar();
    status->addAction(openAction);
    status->addAction(newfileaction);
    status->addAction(savefileaction);
    status->addAction(closeFileAction);
    status->addAction(setClick1);
    status->addAction(setClick2);
    status->addAction(setSlide);
    status->addAction(setPress1);
    status->addAction(setPress2);
    status->addAction(setBpm);
    status->addAction(setPreview);

    menuh=menu->height();
    toolh=toolBar->height();
    stah=status->height();
}

void MainWindow::showAbout()
{
    aboutMessage.setText("0.9.1");
    aboutMessage.setWindowTitle("版本");
    aboutMessage.show();
}

void MainWindow::closeEvent(QCloseEvent *ce)
{
    if(paintzt!=0&&savefileaction->isEnabled()==true)
    {
        closeMessage.setWindowTitle("保存");
        closeMessage.setText("是否保存并退出");
        closeMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        closeMessage.setDefaultButton(QMessageBox::Yes);
        int ret=closeMessage.exec();
        if(ret==QMessageBox::Yes)
        {
            MainWindow::savefile();
            ce->accept();
        }
        else if(ret==QMessageBox::No)
        {
            ce->accept();
        }
        else if(ret==QMessageBox::Cancel)
        {
            ce->ignore();
        }
    }
}

MainWindow::~MainWindow()
{

}
