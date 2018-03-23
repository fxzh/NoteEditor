#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>

class SettingDialog : public QDialog
{
public:
    QDialog *setDialog;
    QTabWidget *tab;
    QWidget *widgetWidget,*widgetOperate;
    QLabel *labInitX,*labInitY,*labDelay,*labSmallbars,*labSmallbarHeight,*labWheelUD,*labWheelDistance,\
           *labNoteStep,*labNoteWidth;
    QLineEdit *textInitX,*textInitY,*textDelay,*textSmallbarHeight,*textNoteStep,*textNoteWidth;
    QComboBox *textSmallbars,*textWheelDistance;
    QButtonGroup *UDGroup;
    QRadioButton *radioUp,*radioDown;
    QGridLayout *widgetLayout,*operateLayout;
    QPushButton *ensure,*cancel;
    SettingDialog();
    void setInitX(int x);
    void setInitY(int y);
    void setDelay(int delay);
    void setSmallBars(int smallbarsIndex);
    void setSmallbarHeight(int smallbarHeight);
    void setWheelUD(int ud);
    void setWheelDistance(int wheelDistanceIndex);
    void setNoteStep(double noteStep);
    void setNoteWidth(double noteWidth);
    int initX() const
    {
        return textInitX->text().toInt();
    }
    int initY() const
    {
        return textInitY->text().toInt();
    }
    int delay() const
    {
        return textDelay->text().toInt();
    }
    int smallbarsIndex() const
    {
        return textSmallbars->currentIndex();
    }
    int smallbarHeight() const
    {
        return textSmallbarHeight->text().toInt();
    }
    int wheelUD() const
    {
        if(radioDown->isChecked())
        {
            return 0;
        }
        else if(radioUp->isChecked())
        {
            return 1;
        }
        else
        {
            return -2;
        }
    }
    int wheelDistanceIndex() const
    {
        return textWheelDistance->currentIndex();
    }
    double noteStep()
    {
        return textNoteStep->text().toDouble();
    }
    double noteWidth()
    {
        return textNoteWidth->text().toDouble();
    }
};

#endif // SETTINGDIALOG_H
