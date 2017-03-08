/****************************************************************************
** Form interface generated from reading ui file 'sigmoid.ui'
**
** Created: Mon Dec 1 00:08:51 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORMSIGMOID_H
#define FORMSIGMOID_H

#include <qvariant.h>
#include <qwidget.h>
#include "network.h"

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FormSigmoid : public QWidget
{ 
    Q_OBJECT

public:
    FormSigmoid( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~FormSigmoid();

    QLabel* TextLabel7;
    QLabel* TextLabel8;
    QLabel* TextLabel9;
    QPushButton* PushButtonOk;
    QLineEdit* LineEditPas;
    QLineEdit* LineEditBornMax;
    QLineEdit* LineEditBornMin;
    QCheckBox* CheckBox2;
	networkFather *monNetwork ;
	void setNetworkFather(networkFather *thisNetwork);
	bool utiliserLaRealFonction();
private slots:
    
    void ok();

};

#endif // FORMSIGMOID_H
