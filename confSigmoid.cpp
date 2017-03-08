/****************************************************************************
** Form implementation generated from reading ui file 'sigmoid.ui'
**
** Created: Mon Dec 1 00:08:57 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "confSigmoid.h"

#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a FormSigmoid which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
FormSigmoid::FormSigmoid( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "FormSigmoid" );
    resize( 288, 196 ); 
    setCaption( tr( "Fonction activation (Signoid)" ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 20, 40, 85, 13 ) ); 
    TextLabel7->setText( tr( "pas ( 2 exp n ) n =" ) );

    TextLabel8 = new QLabel( this, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 20, 70, 108, 13 ) ); 
    TextLabel8->setText( tr( "borne max (2 exp n) n=" ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 20, 100, 105, 13 ) ); 
    TextLabel9->setText( tr( "borne min (2 exp n) n=" ) );

    PushButtonOk = new QPushButton( this, "PushButtonOk" );
    PushButtonOk->setGeometry( QRect( 100, 150, 51, 31 ) ); 
    PushButtonOk->setText( tr( "OK" ) );

    LineEditPas = new QLineEdit( this, "LineEditPas" );
    LineEditPas->setGeometry( QRect( 138, 36, 51, 22 ) ); 
	LineEditPas->setText( tr( "0.25" ) );

    LineEditBornMax = new QLineEdit( this, "LineEditBornMax" );
    LineEditBornMax->setGeometry( QRect( 139, 66, 51, 22 ) ); 
	LineEditBornMax->setText( tr( "5.0" ) );

    LineEditBornMin = new QLineEdit( this, "LineEditBornMin" );
    LineEditBornMin->setGeometry( QRect( 140, 97, 51, 22 ) ); 
	LineEditBornMin->setText( tr( "-5.0" ) );

    CheckBox2 = new QCheckBox( this, "CheckBox2" );
    CheckBox2->setGeometry( QRect( 20, 10, 228, 17 ) ); 
    CheckBox2->setText( tr( "Ne pas utiliser l'approximation (reel fonction)" ) );
	CheckBox2->setChecked (true) ;

	connect( PushButtonOk, SIGNAL(clicked()),this  , SLOT( ok ()) );

}

/*  
 *  Destroys the object and frees any allocated resources
 */
FormSigmoid::~FormSigmoid()
{
    // no need to delete child widgets, Qt does it all for us
}

bool FormSigmoid::utiliserLaRealFonction(){

	return !CheckBox2->isChecked () ;
}
	
void FormSigmoid::setNetworkFather(networkFather *thisNetwork){
	monNetwork=thisNetwork;
}

void FormSigmoid::ok(){
	monNetwork->borneSigmoid =LineEditBornMax->text().toFloat ();
	monNetwork->pasSigmoid=LineEditPas->text().toFloat ();
	monNetwork->workSigmoidApprox=utiliserLaRealFonction();
	hide();
	}

