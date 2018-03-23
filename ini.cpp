#include "mainwindow.h"

void MainWindow::writeAniniFile()
{
    iniSettings=new QSettings(iniPath,QSettings::IniFormat);
    iniSettings->setValue("Geometry/x",setInit->initX());
    iniSettings->setValue("Geometry/y",setInit->initY());
    iniSettings->setValue("Wheel/Direction",setInit->wheelUD());
    iniSettings->setValue("Wheel/DistanceIndex",setInit->wheelDistanceIndex());
    iniSettings->setValue("EditNote/Step",setInit->noteStep());
    iniSettings->setValue("EditNote/Width",setInit->noteWidth());
    iniSettings->setValue("Video/Delay",setInit->delay());
    iniSettings->setValue("Smallbar/NumbarIndex",setInit->smallbarsIndex());
    iniSettings->setValue("Smallbar/px",setInit->smallbarHeight());
    delete iniSettings;
}

void MainWindow::readAniniFile()
{
    iniSettings=new QSettings(iniPath,QSettings::IniFormat);
    screenX=iniSettings->value("Geometry/x").toString().toInt();
    screenY=iniSettings->value("Geometry/y").toString().toInt();
    wheelDirection=iniSettings->value("Wheel/Direction").toString().toInt();
    wheelIndex=iniSettings->value("Wheel/DistanceIndex").toString().toInt();
    editNoteStep=iniSettings->value("EditNote/Step").toString().toDouble();
    dNoteWidth=iniSettings->value("EditNote/Width").toString().toDouble();
    videoDelay=iniSettings->value("Video/Delay").toString().toInt();
    emit sendVideoDelay(videoDelay);
    smallbarIndex=iniSettings->value("Smallbar/NumbarIndex").toString().toInt();
    smallbarPx=iniSettings->value("Smallbar/px").toString().toInt();
    MainWindow::writeSetting();
    delete iniSettings;
}

void MainWindow::createAniniFile()
{
    iniSettings=new QSettings(iniPath,QSettings::IniFormat);
    iniSettings->setValue("Geometry/x",scrw);
    iniSettings->setValue("Geometry/y",scrh);
    iniSettings->setValue("Wheel/Direction",1);
    iniSettings->setValue("Wheel/DistanceIndex",0);
    iniSettings->setValue("EditNote/Step",0.01);
    iniSettings->setValue("EditNote/Width",1);
    iniSettings->setValue("Video/Delay",5);
    iniSettings->setValue("Smallbar/NumbarIndex",7);
    iniSettings->setValue("Smallbar/px",50);
    delete iniSettings;
}

void MainWindow::writeSetting()
{
    setInit=new SettingDialog();
    setInit->setGeometry(scrw/2-125,scrh/2-110,250,220);
    setInit->setWindowTitle("设置");
    connect(setInit->ensure,SIGNAL(clicked(bool)),this,SLOT(settingEnsureButton()));
    connect(setInit->cancel,SIGNAL(clicked(bool)),this,SLOT(settingCancelButton()));
    setInit->setInitX(screenX);
    setInit->setInitY(screenY);
    setInit->setWheelUD(wheelDirection);
    setInit->setWheelDistance(wheelIndex);
    setInit->setNoteStep(editNoteStep);
    setInit->setNoteWidth(dNoteWidth);
    setInit->setDelay(videoDelay);
    setInit->setSmallBars(smallbarIndex);
    setInit->setSmallbarHeight(smallbarPx);
}
