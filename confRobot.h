/****************************************************************************
** Form interface generated from reading ui file 'robot.ui'
**
** Created: Sun Nov 30 23:11:34 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORMROBOTCONF_H
#define FORMROBOTCONF_H

#include <qvariant.h>
#include <qwidget.h>
#include "robot.h"

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class FormRobotConf : public QWidget
{ 
    Q_OBJECT

public:
    FormRobotConf( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~FormRobotConf();

    QLabel* TextLabelnbrCapt;
    QLineEdit* LineEditNombreCapteur;
    QLineEdit* LineEditDestAvance;
    QLineEdit* LineEditTimeCycle;
    QLineEdit* LineEditMaxAngLearn;
    QLineEdit* LineEditMaxAngExec;
    QLineEdit* LineEditDestImpact;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel5;
    QLabel* TextLabel6;
    QLabel* TextLabel4;
    QPushButton* PushButtonOK;
	Robot* monRobot;
	void setRobot(Robot *ThisRobot);
public slots:
    
    void ok();

};

#endif // FORMROBOTCONF_H
