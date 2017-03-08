/****************************************************************************
** Form implementation generated from reading ui file 'montest.ui'
**
** Created: Fri Nov 28 23:13:04 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frameChoitArth.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <QButtonGroup.h>


/* 
 *  Constructs a FormchoitArithmetique which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
FormchoitArithmetique::FormchoitArithmetique( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "FormchoitArithmetique" );
    resize( 318, 336 ); 
    setCaption( tr( "Choix du type d'arithmeique a utilise:" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 40, 160, 133, 13 ) ); 
    TextLabel2->setText( tr( "Parametre de l'arithmetique :" ) );

    LineEditMantissa = new QLineEdit( this, "LineEditMantissa" );
    LineEditMantissa->setGeometry( QRect( 120, 187, 40, 22 ) ); 
    LineEditMantissa->setText( tr( "15" ) );

    LineEditExposant = new QLineEdit( this, "LineEditExposant" );
    LineEditExposant->setGeometry( QRect( 120, 217, 40, 22 ) ); 
    LineEditExposant->setText( tr( "15" ) );

    PushButtonOk = new QPushButton( this, "PushButtonOk" );
    PushButtonOk->setGeometry( QRect( 71, 270, 70, 41 ) ); 
    PushButtonOk->setText( tr( "Ok" ) );

    PushButtonAnnuler = new QPushButton( this, "PushButtonAnnuler" );
    PushButtonAnnuler->setGeometry( QRect( 150, 270, 70, 41 ) ); 
    PushButtonAnnuler->setText( tr( "Annuler" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 40, 30, 130, 13 ) ); 
    TextLabel1->setText( tr( "Type d'arithmeique a utilise:" ) );

    TextLabMontissa = new QLabel( this, "TextLabMontissa" );
    TextLabMontissa->setGeometry( QRect( 71, 190, 41, 13 ) ); 
    TextLabMontissa->setText( tr( "mantisse" ) );

    TextLabExposant = new QLabel( this, "TextLabExposant" );
    TextLabExposant->setGeometry( QRect( 71, 222, 43, 13 ) ); 
    TextLabExposant->setText( tr( "exposant" ) );

    RadioFloatPc = new QRadioButton( this, "RadioFloatPc" );
    RadioFloatPc->setGeometry( QRect( 80, 120, 115, 17 ) ); 
    RadioFloatPc->setBackgroundOrigin( QRadioButton::WidgetOrigin );
    RadioFloatPc->setText( tr( "Floating point du PC" ) );

    RadioFloatVr = new QRadioButton( this, "RadioFloatVr" );
    RadioFloatVr->setGeometry( QRect( 80, 90, 112, 17 ) ); 
    RadioFloatVr->setBackgroundOrigin( QRadioButton::WidgetOrigin );
    RadioFloatVr->setText( tr( "Virtual floating point" ) );

    RadioFixet = new QRadioButton( this, "RadioFixet" );
    RadioFixet->setGeometry( QRect( 80, 60, 100, 17 ) ); 
    RadioFixet->setBackgroundOrigin( QRadioButton::WidgetOrigin );
    RadioFixet->setText( tr( "Virtual fixed point" ) );

	bg = new QButtonGroup(this);
    
	bg->hide();
    bg->insert(RadioFloatPc,0);
    bg->insert(RadioFloatVr,1);
    bg->insert(RadioFixet,2);
	RadioFloatPc->setChecked(TRUE);changeMode(0);
    
	connect( bg, SIGNAL(clicked(int)), SLOT(changeMode(int)) );
	connect( PushButtonAnnuler, SIGNAL(clicked()),this  , SLOT( hide ()) );
	connect( PushButtonOk, SIGNAL(clicked()),this  , SLOT( hide ()) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
FormchoitArithmetique::~FormchoitArithmetique()
{
    // no need to delete child widgets, Qt does it all for us
}
 void FormchoitArithmetique::changeMode(int i){
		
		if (i==0) {
			//Pc float
			LineEditMantissa->setReadOnly  (true);
			LineEditExposant->setReadOnly  (true);
			LineEditMantissa->setText( tr( "24" ) );
			LineEditExposant->setText( tr( "8" ) );
			TextLabMontissa->setText( tr( "mantisse" ) );
			TextLabExposant->setText( tr( "exposant" ) );

		}
		if (i==1) {
			//virtual float
			
			LineEditMantissa->setReadOnly  (false);
			LineEditExposant->setReadOnly  (false);
			LineEditMantissa->setText( tr( "15" ) );
			LineEditExposant->setText( tr( "15" ) );
			TextLabMontissa->setText( tr( "mantisse" ) );
			TextLabExposant->setText( tr( "exposant" ) );
		}
		if (i==2) {
			//fixed point
			LineEditMantissa->setReadOnly  (false);
			LineEditExposant->setReadOnly  (false);
			LineEditMantissa->setText( tr( "10" ) );
			LineEditExposant->setText( tr( "10" ) );
			TextLabMontissa->setText( tr( "avant','" ) );
			TextLabExposant->setText( tr( "apres','" ) );
		}
		
};
   
bool FormchoitArithmetique::isPcFloatingPoint()
{		
	return (RadioFloatPc->isChecked ());
};
bool FormchoitArithmetique::isVFloatingPoint()
{		
	return (RadioFloatVr->isChecked ());
};
bool FormchoitArithmetique::isFixedPoint()
{		
	return (RadioFixet->isChecked ());
};

int FormchoitArithmetique::getFirstParm()
{//exposant    apres vergule

	return (LineEditExposant->text().toInt()); 

}
int FormchoitArithmetique::getSecndParm()
{//mantice    avant vergule

	return (LineEditMantissa->text().toInt()); 
}
