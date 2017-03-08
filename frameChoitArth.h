/****************************************************************************
** Form interface generated from reading ui file 'montest.ui'
**
** Created: Fri Nov 28 23:15:40 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORMCHOITARITHMETIQUE_H
#define FORMCHOITARITHMETIQUE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QButtonGroup;

class FormchoitArithmetique : public QWidget
{ 
    Q_OBJECT

public:
    FormchoitArithmetique( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~FormchoitArithmetique();

	QButtonGroup *bg;
    QLabel* TextLabel2;
    QLineEdit* LineEditMantissa;
    QLineEdit* LineEditExposant;
    QPushButton* PushButtonOk;
    QPushButton* PushButtonAnnuler;
    QLabel* TextLabel1;
    QLabel* TextLabMontissa;
    QLabel* TextLabExposant;
    QRadioButton* RadioFloatPc;
    QRadioButton* RadioFloatVr;
    QRadioButton* RadioFixet;
	bool isPcFloatingPoint();
	bool isVFloatingPoint();
	bool isFixedPoint();
	int getFirstParm();
	int getSecndParm();

private slots:
    
    void changeMode(int i);
};

#endif // FORMCHOITARITHMETIQUE_H
