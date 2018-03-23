#include "settingdialog.h"

SettingDialog::SettingDialog()
{
    setDialog=new QDialog();
    tab=new QTabWidget(this);
    widgetWidget=new QWidget();
    widgetOperate=new QWidget();

    widgetLayout=new QGridLayout(widgetWidget);
    operateLayout=new QGridLayout(widgetOperate);
    widgetLayout->setColumnStretch(2,5);
    operateLayout->setColumnStretch(3,4);

    labInitX=new QLabel("初始窗口长度");
    labInitY=new QLabel("初始窗口高度");
    labDelay=new QLabel("播放延迟");
    labSmallbars=new QLabel("初始小节数");
    labSmallbarHeight=new QLabel("初始小节高度");
    textInitX=new QLineEdit();
    textInitX->setValidator(new QIntValidator(10,10000,this));
    textInitY=new QLineEdit();
    textInitY->setValidator(new QIntValidator(10,10000,this));
    textDelay=new QLineEdit();
    textDelay->setValidator(new QIntValidator(1,100,this));
    textSmallbars=new QComboBox();
    QStringList sblist;
    sblist<<"1"<<"2"<<"3"<<"4"<<"6"<<"8"<<"12"<<"16"<<"24"<<"32"<<"48"<<"64";
    textSmallbars->addItems(sblist);
    textSmallbarHeight=new QLineEdit();
    textSmallbarHeight->setValidator(new QIntValidator(10,1000,this));

    widgetLayout->addWidget(labInitX,0,0);
    widgetLayout->addWidget(labInitY,1,0);
    widgetLayout->addWidget(labDelay,2,0);
    widgetLayout->addWidget(labSmallbars,3,0);
    widgetLayout->addWidget(labSmallbarHeight,4,0);
    widgetLayout->addWidget(textInitX,0,1);
    widgetLayout->addWidget(textInitY,1,1);
    widgetLayout->addWidget(textDelay,2,1);
    widgetLayout->addWidget(textSmallbars,3,1);
    widgetLayout->addWidget(textSmallbarHeight,4,1);

    labWheelUD=new QLabel("鼠标滚轮方向");
    labWheelDistance=new QLabel("鼠标滚轮距离");
    labNoteStep=new QLabel("Note大小改变量");
    labNoteWidth=new QLabel("初始Note大小");
    UDGroup=new QButtonGroup();
    UDGroup->setExclusive(true);
    radioUp=new QRadioButton();
    radioUp->setText("正向");
    radioDown=new QRadioButton();
    radioDown->setText("反向");
    UDGroup->addButton(radioUp);
    UDGroup->addButton(radioDown);
    textWheelDistance=new QComboBox();
    QStringList wd;
    wd<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8";
    textWheelDistance->addItems(wd);
    textNoteStep=new QLineEdit();
    textNoteStep->setValidator(new QDoubleValidator(0.00001,5,5,this));
    textNoteWidth=new QLineEdit();
    textNoteWidth->setValidator(new QDoubleValidator(0.05,5,5,this));
    operateLayout->addWidget(labWheelUD,0,0);
    operateLayout->addWidget(labWheelDistance,1,0);
    operateLayout->addWidget(labNoteStep,2,0);
    operateLayout->addWidget(labNoteWidth,3,0);
    operateLayout->addWidget(radioUp,0,1);
    operateLayout->addWidget(radioDown,0,2);
    operateLayout->addWidget(textWheelDistance,1,1,1,-1);
    operateLayout->addWidget(textNoteStep,2,1,1,-1);
    operateLayout->addWidget(textNoteWidth,3,1,1,-1);

    tab->addTab(widgetWidget,"界面");
    tab->addTab(widgetOperate,"操作");
    ensure=new QPushButton("确定",this);
    cancel=new QPushButton("取消",this);
    ensure->setGeometry(30,180,70,30);
    cancel->setGeometry(140,180,70,30);
}

void SettingDialog::setInitX(int x)
{
    textInitX->setText(QString("%1").arg(x));
}

void SettingDialog::setInitY(int y)
{
    textInitY->setText(QString("%1").arg(y));
}

void SettingDialog::setDelay(int delay)
{
    textDelay->setText(QString("%1").arg(delay));
}

void SettingDialog::setSmallBars(int smallbarsIndex)
{
    textSmallbars->setCurrentIndex(smallbarsIndex);
}

void SettingDialog::setSmallbarHeight(int smallbarHeight)
{
    textSmallbarHeight->setText(QString("%1").arg(smallbarHeight));
}

void SettingDialog::setWheelUD(int ud)
{
    if(ud==0)
    {
        radioDown->setChecked(true);
    }
    else if(ud==1)
    {
        radioUp->setChecked(true);
    }
}

void SettingDialog::setWheelDistance(int wheelDistanceIndex)
{
    textWheelDistance->setCurrentIndex(wheelDistanceIndex);
}

void SettingDialog::setNoteStep(double noteStep)
{
    textNoteStep->setText(QString("%1").arg(noteStep));
}

void SettingDialog::setNoteWidth(double noteWidth)
{
    textNoteWidth->setText(QString("%1").arg(noteWidth));
}
