/****************************************************************************
** Form implementation generated from reading ui file 'robot.ui'
**
** Created: Sun Nov 30 23:12:38 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "confRobot.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a FormRobotConf which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
FormRobotConf::FormRobotConf( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "FormRobotConf" );
    resize( 318, 334 ); 
    setCaption( tr( "parametre du robot" ) );

    TextLabelnbrCapt = new QLabel( this, "TextLabelnbrCapt" );
    TextLabelnbrCapt->setGeometry( QRect( 30, 40, 103, 13 ) ); 
    TextLabelnbrCapt->setText( tr( "Nombre de capteur   :" ) );
	 

    LineEditNombreCapteur = new QLineEdit( this, "LineEditNombreCapteur" );
    LineEditNombreCapteur->setGeometry( QRect( 200, 37, 51, 22 ) ); 
	LineEditNombreCapteur->setText( tr( "8" ) );

    LineEditDestAvance = new QLineEdit( this, "LineEditDestAvance" );
    LineEditDestAvance->setGeometry( QRect( 200, 77, 51, 22 ) ); 
	LineEditDestAvance->setText( tr( "10" ) );

    LineEditTimeCycle = new QLineEdit( this, "LineEditTimeCycle" );
    LineEditTimeCycle->setGeometry( QRect( 200, 107, 51, 22 ) ); 
	LineEditTimeCycle->setText( tr( "100" ) );

    LineEditMaxAngLearn = new QLineEdit( this, "LineEditMaxAngLearn" );
    LineEditMaxAngLearn->setGeometry( QRect( 200, 147, 51, 22 ) ); 
	LineEditMaxAngLearn->setText( tr( "90" ) );

    LineEditMaxAngExec = new QLineEdit( this, "LineEditMaxAngExec" );
    LineEditMaxAngExec->setGeometry( QRect( 200, 187, 51, 22 ) ); 
	LineEditMaxAngExec->setText( tr( "40" ) );

    LineEditDestImpact = new QLineEdit( this, "LineEditDestImpact" );
    LineEditDestImpact->setGeometry( QRect( 235, 227, 51, 22 ) ); 
	LineEditDestImpact->setText( tr( "16" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 30, 80, 153, 13 ) ); 
    TextLabel2->setText( tr( "Destance a avancer  par cycle  :" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 30, 114, 90, 13 ) ); 
    TextLabel3->setText( tr( "Periode du cycle  :" ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 30, 150, 146, 13 ) ); 
    TextLabel5->setText( tr( "Angle maximal d'aprentisage   :" ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 30, 190, 123, 13 ) ); 
    TextLabel6->setText( tr( "Angle maximal en exec   :" ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 30, 230, 196, 13 ) ); 
    TextLabel4->setText( tr( "Destance d'impacte pour le superviseur :" ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 110, 280, 91, 40 ) ); 
    PushButtonOK->setText( tr( "OK" ) );
	connect( PushButtonOK, SIGNAL(clicked()),this  , SLOT( ok ()) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
FormRobotConf::~FormRobotConf()
{
    // no need to delete child widgets, Qt does it all for us
}

void FormRobotConf::ok(){
	monRobot->nbrCapteur =LineEditNombreCapteur->text().toInt();
	monRobot->MaxOngleForLearn=LineEditMaxAngLearn->text().toInt();
	monRobot->MaxOngleForExec=LineEditMaxAngExec->text().toInt();
	monRobot->timetoAvance=LineEditTimeCycle->text().toInt();
	monRobot->destanceToAvance=LineEditDestAvance->text().toInt();
	monRobot->ImpactDistance=LineEditDestImpact->text().toInt();
	hide();
	}
void FormRobotConf::setRobot(Robot *ThisRobot){monRobot=ThisRobot;};



