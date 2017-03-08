/*****************************************************************************
**																	 		**
** Robot qui evite les obstacle												**
** en utilisant les reseaux de neurone ML									**
**																			**
** cette application est une simulation du robot Kapera qui					**
** est composer de 8 capteur												**
** Copyright (C) 1992-2000 chouba nabil  All rights reserved.				**
**																			**
**																			**
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "connect.h"
#include <qmessagebox.h> 
#include <qlcdnumber.h>
#include <qfiledialog.h> 
#include "imge.h"
#include <QPopupMenu.h>
#include <QMenuBar.h>
static QMutex* mutex;


#include <qthread.h> 


class MyThread : public QThread {
	    Q_OBJECT

  public:
	networkFather *nnt;
	bool endExec;
    virtual void run();
	FormCourbe *monFormCourbe;

  };

  void MyThread::run()
  {
	  bool removeLast=false;

	  QList<QPoint> *errorGraph=monFormCourbe->TabErrorGraph[monFormCourbe->curentGraph-1];

	  endExec= false;
	  
	  while (1){
		 
	while (!nnt->StopLearn)
	{
		mutex->lock();
		int curError=(int) (nnt->launchLearn()*10000);
		mutex->unlock();

		if (!errorGraph->isEmpty()){
			if( errorGraph->getLast()->y() - curError >20 ||  curError -errorGraph->getLast()->y()  >20 ){
		      errorGraph->append ( new QPoint(nnt->setp,curError));
			  
			  monFormCourbe->courbeDraw();
			  removeLast=false;
			  qWarning("step=%d %d",nnt->setp,errorGraph->count () );
			}
			else {
				//if (removeLast){
				   // errorGraph->getLast   ()->setX (nnt->setp);
					//errorGraph->getLast  ()->setY (curError);
				 
				//}else
				  errorGraph->append ( new QPoint(nnt->setp,curError));
				  //removeLast=true;
				  
				  monFormCourbe->courbeDraw();
			}
		}
		else 
			errorGraph->append ( new QPoint(nnt->setp,curError));
		
		if ( endExec ) return;
	}	
	if ( endExec ) return;
	  sleep(1);
	  }


  }




#define ModeProbg 0
#define ModeLearn 1
#define ModeDrawObstcle 2
MyThread a;

//#define MaxOngle 10			//l angle maximal que peux faire le robot
//#define ImpactDistance 16	//la distance que declanche l`appretissage on line
//#define PERIODE_AVANCE 100	//periode de temp donner au timer pour l'avancement
//
// Constructs a ConnectWidget.
//

ConnectWidget::ConnectWidget( QWidget *parent, const char *name )
 : QWidget( parent, name, WNorthWestGravity )
{
	stateMode=ModeProbg;
	

	resize( 892, 670 ); 
	PixmapLearnOk =new QPixmap( ( const char** ) (imageLearnOk) );
	PixmapInLearn =new QPixmap( ( const char** ) (imageInLearn) );


	 pixmapModeStyle=new QPixmap( ( const char** ) imageModeStyle );
     pixmapStyleLoad=new QPixmap( ( const char** ) imageStyleLoad );
     pixmapStyleSave=new QPixmap( ( const char** ) imageStyleSave );
     pixmapShowObstacle=new QPixmap( ( const char** ) imageShowObstacle );
     pixmapOnLineLearn=new QPixmap( ( const char** ) imageOnLineLearn );
     pixmapAvancePasAPas=new QPixmap( ( const char** ) imageAvancePasAPas );
     pixmapSaveW=new QPixmap( ( const char** ) imageSaveW );
     pixmapLoadW=new QPixmap( ( const char** ) imageLoadW );
     pixmapFilter=new QPixmap( ( const char** ) imageFilter );
     pixmapOffLineLearn=new QPixmap( ( const char** ) imageOffLineLearn );
     pixmapGoRobot=new QPixmap( ( const char** ) imageGoRobot );
     pixmapStopRobot=new QPixmap( ( const char** ) imageStopRobot );
     pixmapLaunchLearn=new QPixmap( ( const char** ) imageLaunchLearn );

	ButtonSaveW = new QPushButton( this, "ButtonSaveW" );
    ButtonSaveW->setGeometry( QRect( 320, 20, 40, 41 )); 
    ButtonSaveW->setText( tr( "Save Weights" ) );
	ButtonSaveW->setPixmap(* pixmapSaveW );

    ButtonLoadW = new QPushButton( this, "ButtonLoadW" );
    ButtonLoadW->setGeometry( QRect( 360, 20, 40, 41 )  ); 
    ButtonLoadW->setText( tr( "Load Weights" ) );
	ButtonLoadW->setPixmap(* pixmapLoadW );

	ButtonGoStopRobot = new QPushButton( this, "ButtonGoStopRobot" );
    ButtonGoStopRobot->setGeometry( QRect( 280, 20, 40, 41 ) ); 
    ButtonGoStopRobot->setText( tr( "Avance / arrette robot" ) );
	ButtonGoStopRobot->setPixmap(* pixmapGoRobot );


    ButtonLearnStyle = new QPushButton( this, "ButtonLearnStyle" );
    ButtonLearnStyle->setGeometry( QRect( 0, 20, 40, 41 )); 
    ButtonLearnStyle->setText( tr( "learn style" ) );
	ButtonLearnStyle->setPixmap(* pixmapModeStyle );

    ButtonLaunchLearn = new QPushButton( this, "ButtonLaunchLearn" );
    ButtonLaunchLearn->setGeometry( QRect( 160, 20, 40, 41 ) ); 
    ButtonLaunchLearn->setText( tr( "Launch learn" ) );
	ButtonLaunchLearn->setPixmap(* pixmapLaunchLearn );

    ButtonAvancePasAPas = new QPushButton( this, "ButtonAvancePasAPas" );
    ButtonAvancePasAPas->setGeometry( QRect( 240, 20, 40, 41 )); 
    ButtonAvancePasAPas->setText( tr( "Avance pas a pas" ) );
	ButtonAvancePasAPas->setPixmap(* pixmapAvancePasAPas );


	ButtonFilter = new QPushButton( this, "ButtonFilter" );
    ButtonFilter->setGeometry( QRect( 400, 20, 40, 41 ) ); 
    ButtonFilter->setText( tr( "FilterStyle" ) );
	ButtonFilter->setPixmap(* pixmapFilter );


	ButtonLoadStyle = new QPushButton( this, "ButtonLoadStyle" );
    ButtonLoadStyle->setGeometry( QRect( 40, 20, 40, 41 ) ); 
    ButtonLoadStyle->setText( tr( "Load Style" ) );
	ButtonLoadStyle->setPixmap(* pixmapStyleLoad );


	ButtonShowObstacle = new QPushButton( this, "ButtonShowObstacle" );
    ButtonShowObstacle->setGeometry( QRect( 120, 20, 40, 41 ) ); 
    ButtonShowObstacle->setText( tr( "show obstacl" ) );
	ButtonShowObstacle->setPixmap(* pixmapShowObstacle );


    ButtonOnLineLearn = new QPushButton( this, "ButtonOnLineLearn" );
    ButtonOnLineLearn->setGeometry( QRect( 200, 20, 40, 41 ) ); 
    ButtonOnLineLearn->setText( tr( "On line learn" ) );
	ButtonOnLineLearn->setPixmap(* pixmapOnLineLearn );

    
    LCDErr = new QLCDNumber( this, "LCDErr" );
    LCDErr->setGeometry(QRect( 650, 20, 181, 41 )  ); 
    LCDErr->setNumDigits( 7 );

    ButtonLearnInfo = new QPushButton( this, "ButtonLearnInfo" );
    ButtonLearnInfo->setGeometry( QRect( 830, 20, 60, 41 ) ); 
    ButtonLearnInfo->setText( tr( "" ) );


    ButtonSaveStyle = new QPushButton( this, "ButtonSaveStyle" );
    ButtonSaveStyle->setGeometry( QRect( 80, 20, 40, 42 ) ); 
    ButtonSaveStyle->setText( tr( "Save Style" ) );
	ButtonSaveStyle->setPixmap(* pixmapStyleSave );


    LCDStep = new QLCDNumber( this, "LCDStep" );
    LCDStep->setGeometry( QRect( 487, 20, 120, 41 )  ); 
    LCDStep->setNumDigits( 7 );

    TextStep = new QLabel( this, "TextStep" );
    TextStep->setGeometry( QRect( 440, 20, 47, 41 )); 
    TextStep->setText( tr( "StepLearn:" ) );
    
	TextError = new QLabel( this, "ErrorStep" );
    TextError->setGeometry( QRect( 608, 20, 42, 41)); 
    TextError->setText( tr( "error:" ) );


	ButtonLearnInfo->setPixmap( *PixmapLearnOk );



    timer =new QTimer( this );
    timer->stop ();
	connect( timer, SIGNAL(timeout()), SLOT(avanceRobot()) );
	 

	setBackgroundColor( white );		// white background
 
    colors = new QColor[MAXCOLORS];
	pointMyFin= new QPoint();
	pointMyDebut= new QPoint();
    for ( int i=0; i<MAXCOLORS; i++ )		// init color array
	colors[i] = QColor( rand()&255, rand()&255, rand()&255 );
	
	//trajet a faire par le robot
	path= new QList<QPoint>();

	

	//envirenement des obstacle ...
//	envrnemt = new QList<obstacle>();
	envObstacle =new enverenement();
	//load obstacle (static pour le moment)

/*	envrnemt->append (new obstacle(QPoint(-1,0),QPoint(0,10)));
	envrnemt->append (new obstacle(QPoint(0,-1),QPoint(10,0)));
	envrnemt->append (new obstacle(QPoint(10,0),QPoint(11,10)));
	envrnemt->append (new obstacle(QPoint(0,10),QPoint(10,11)));

	envrnemt->append (new obstacle(QPoint(2,7),QPoint(4,8)));
	envrnemt->append (new obstacle(QPoint(3,3),QPoint(5,5)));
	envrnemt->append (new obstacle(QPoint(7,1),QPoint(9,4)));
	envrnemt->append (new obstacle(QPoint(7,5),QPoint(9,6)));
*/
	actualPos = new QPoint(10,10);

	robotMover = new Robot(QPoint(250,250),0,8);
	
	robotMover->setObstacle(envObstacle->ensembleObstacle);


	
	OnLineLearn=true;


	nnt =new network<FixedPoint>();

	n=new net();
	n->usedNetWork =nnt;
	nnt->LCDErr=LCDErr;
	nnt->LCDstep= LCDStep;
	newLoadVecteur=false;


	
	monArethemetique=new FormchoitArithmetique(this,"cooool",Qt::WType_Modal);
	
	monFormRobotConf=new FormRobotConf (this,"cooool",Qt::WType_Modal);
	monFormRobotConf->setRobot(robotMover);
	monFormRobotConf->ok();
	
	monFormSigmoid =new FormSigmoid (this,"cooool",Qt::WType_Modal);
	monFormSigmoid->setNetworkFather(nnt);

	monFormCourbe =new	FormCourbe ();
	


	// Create a menu
    QPopupMenu *styleMenu = new QPopupMenu( this );
	styleMenu->insertTearOffHandle();
    styleMenu->insertItem( "Draw learn style", this,SLOT(learnStyle() ));
    styleMenu->insertItem( "Save learn style",  this, SLOT(saveTrajet()), CTRL+Key_Q );
	styleMenu->insertItem( "Load learn style",  this, SLOT(loadStyle ()));
	styleMenu->insertItem( "Filter learn style",  this, SLOT(ButtonFilterF()));

	QPopupMenu *obstacleMenu = new QPopupMenu( this );
	obstacleMenu->insertTearOffHandle();
    obstacleMenu->insertItem( "Draw obstacle mode", this,SLOT(drawObstacleMode() ));
	obstacleMenu->insertItem( "delete all obstacle", this,SLOT(deleteAllObstacle() ));
    obstacleMenu->insertItem( "Save obstacle",  this, SLOT(ButtonSaveObstacle()) );
	obstacleMenu->insertItem( "Load obstacle",  this, SLOT(ButtonLoadObstacle ()));
	obstacleMenu->insertItem( "Random obstacle",  this, SLOT(notyet()));
	obstacleMenu->insertItem( "Hide/Show obstacle",  this, SLOT(ShowObstacle()));


	QPopupMenu *learnMenu = new QPopupMenu( this );
	learnMenu->insertTearOffHandle();
    learnMenu->insertItem( "Launch learn", this,SLOT(launchLearn() ));
    learnMenu->insertItem( "On line learn",  this, SLOT(OnLineLearnF()) );
	learnMenu->insertItem( "Save etat (Weights)",  this, SLOT(ButtonSaveWF ()));
	learnMenu->insertItem( "Load etat (Weights)",  this, SLOT(ButtonLoadWF()));
	
	QPopupMenu *RobotMenu = new QPopupMenu( this );
	RobotMenu->insertTearOffHandle();
    RobotMenu->insertItem( "Avance pas a pas", this,SLOT(avanceRobot() ));
    RobotMenu->insertItem( "Avance/arret",  this, SLOT(avanceRobotAll()) );
	RobotMenu->insertItem( "Parametre du robot",  this, SLOT(showConfRobt()));

	QPopupMenu *MathMenu = new QPopupMenu( this );
	MathMenu->insertTearOffHandle();
    MathMenu->insertItem( "Arithmetique", this,SLOT(showConfArethemetique() ));
    MathMenu->insertItem( "Sigmoid", this,SLOT(showConfSigmoid() ));

	QPopupMenu *HelpMenu = new QPopupMenu( this );
    HelpMenu->insertItem( "Manual", this,SLOT(notyet() ));
    HelpMenu->insertItem( "About ANN38", this,SLOT(showAbout() ));


    // Create a menu bar
    QMenuBar *m = new QMenuBar( this );
    m->setSeparator( QMenuBar::InWindowsStyle );
    m->insertItem("&Style", styleMenu );
    m->insertItem("&Obstacle", obstacleMenu );
	m->insertItem("&Learn", learnMenu );
	m->insertItem("&Robot", RobotMenu );
	m->insertItem("&Math", MathMenu );
	m->insertItem("&Help", HelpMenu );

	connect( ButtonSaveW, SIGNAL(clicked()),this  , SLOT(ButtonSaveWF()) );
	connect( ButtonLoadW, SIGNAL(clicked()),this  , SLOT(ButtonLoadWF()) );
	connect( ButtonOnLineLearn, SIGNAL(clicked()),this  , SLOT(OnLineLearnF()) );
	connect( ButtonAvancePasAPas, SIGNAL(clicked()),this  , SLOT(avanceRobot()) );
	connect( ButtonGoStopRobot, SIGNAL(clicked()),this  , SLOT(avanceRobotAll()) );
	connect( ButtonLaunchLearn, SIGNAL(clicked()),this  , SLOT(launchLearn()) );
	connect( ButtonSaveStyle, SIGNAL(clicked()),this  , SLOT(saveTrajet()) );
	connect( ButtonShowObstacle, SIGNAL(clicked()),this  , SLOT(ShowObstacle()) );
	connect( ButtonLearnStyle, SIGNAL(clicked()),this  , SLOT(learnStyle()) );
	connect( ButtonLearnInfo, SIGNAL(clicked()),this  , SLOT( stopLearnF ()) );
	connect( ButtonLoadStyle, SIGNAL(clicked()),this  , SLOT( loadStyle ()) );
	connect( ButtonFilter, SIGNAL(clicked()),this  , SLOT( ButtonFilterF ()) );


	PHautGauche =new QPoint(0,0);
	PBasDroit   =new QPoint(0,0);
	envObstacle->load("save_obstacle.txt");

		

}
void ConnectWidget::showConfRobt(){monFormRobotConf->show ();}
void ConnectWidget::showConfSigmoid(){monFormSigmoid->show();}
void ConnectWidget::showConfArethemetique(){monArethemetique->show();}
void ConnectWidget::showAbout()
{
     QMessageBox::about( this, "ANN ML for avoiding obstacl (N°380)",
                         "ANN38 est une application qui permet de simuler\n"
						 "le comportement d un robot via defferent parametre\n"
						 "pour bien choisir le model hardware\n\n"
                         "Copyright 2003-2004 .  "
                         "License Free\n\n"
                         "For technical support, nabil.chouba@gmail.com or see\n"
                         "http://www.kodyha.com\n" );
}

void ConnectWidget::notyet(){
	QMessageBox::information( this, "inder Consturction ....","not yet ... next week..." );
}
void ConnectWidget::ButtonSaveWF()
{
	 QString save(QFileDialog::getSaveFileName( "save_Widget.txt", "*.*", this ));
    
	//conversion de Strig a *char
	char file[200];
	for(int i=0;i< (int) (save.length ()) ;i++)
		file[i] =(char) save.ref(i);
	file[i] =0;

	if (save.length () >0 )
		nnt->save_w(file);


}
void ConnectWidget::ButtonLoadWF()
{
	QString load(QFileDialog::getOpenFileName( "save_Widget.txt", "*.*", this ));
    
	//conversion de Strig a *char
	char file[200];
	for(int i=0;i< (int) (load.length ()) ;i++)
		file[i] =(char) load.ref(i);
	file[i] =0;

	if (load.length () >0 )
		nnt->Load_w(file);
}

void ConnectWidget::OnLineLearnF()
{
	
	if (OnLineLearn){
	  ButtonOnLineLearn->setText("not online learn");
	  ButtonOnLineLearn->setPixmap( *pixmapOffLineLearn );
	}
	else {
	  ButtonOnLineLearn->setText("online learn");
	  ButtonOnLineLearn->setPixmap( *pixmapOnLineLearn );
	}

	OnLineLearn = !OnLineLearn;
}

void ConnectWidget::stopLearnF()
{
//	monFormSigmoid->show();
//	monFormRobotConf->show();
//	monArethemetique->show();
//envObstacle->save("cool.txt");
//envObstacle->load("cool.txt");

	monFormCourbe->show ();
	monFormCourbe->setActiveWindow () ;

	
	if (nnt->StopLearn){
	  ButtonLearnInfo->setPixmap( *PixmapInLearn );
	  monFormCourbe->clearAllCourbe->setDisabled  (true);
	}
	else{
	  ButtonLearnInfo->setPixmap( *PixmapLearnOk ); 
	  monFormCourbe->clearAllCourbe->setEnabled (true);
	}
	nnt->StopLearn = !nnt->StopLearn;

}

void ConnectWidget::ButtonSaveObstacle()
{
	 QString save(QFileDialog::getSaveFileName( "save_obstacle.txt", "*.*", this ));
    
	//conversion de Strig a *char
	char file[200];
	for(int i=0;i< (int) (save.length ()) ;i++)
		file[i] =(char) save.ref(i);
	file[i] =0;

	if (save.length () >0 )
		envObstacle->save(file);


	update();
}
void ConnectWidget::ButtonLoadObstacle()
{
	QString load(QFileDialog::getOpenFileName( "save_obstacle.txt", "*.*", this ));
    
	//conversion de Strig a *char
	char file[200];
	for(int i=0;i< (int) (load.length ()) ;i++)
		file[i] =(char) load.ref(i);
	file[i] =0;

	if (load.length () >0 )
		envObstacle->load(file);

	update();
}


void ConnectWidget::ShowObstacle()
{

	envObstacle->inversVisibliter();
	update();

}

void ConnectWidget::learnStyle()
{

//	learnStyl = !learnStyl;
	stateMode++;//0,1 soit mode probagation soit mode learn
	if (stateMode>=2) stateMode=0;
	update();

	if(stateMode==ModeLearn)
	{
		delete path;
		path= new QList<QPoint>();
	}

}
void ConnectWidget::launchLearn()
{	
	monFormCourbe->clearAllCourbe->setDisabled  (true);
	monFormCourbe->show ();
	monFormCourbe->setActiveWindow () ;


	//add new graph
	monFormCourbe->TabErrorGraph[monFormCourbe->curentGraph]= new QList<QPoint>();
	monFormCourbe->curentGraph++;

	//kill thread !!!
	a.endExec = true;
	while (a.running ()) ;
	
//repaint();

	FixedPoint::ExpoBit=monArethemetique->getFirstParm();
	FixedPoint::MontiBit=monArethemetique->getSecndParm();

	VirtalFloat::ExpoBit=monArethemetique->getFirstParm();
	VirtalFloat::MontiBit=monArethemetique->getSecndParm();

	if (nnt!=NULL) 
		delete (nnt);
	nnt=NULL;

	if (monArethemetique->isVFloatingPoint())	
		nnt =new network<VirtalFloat>();
	else if (monArethemetique->isFixedPoint())		
		nnt =new network<FixedPoint>();
	else if (monArethemetique->isPcFloatingPoint())	
		nnt =new network<float>();

	monFormSigmoid->setNetworkFather(nnt);


	
	n->usedNetWork =nnt;
	nnt->LCDErr=LCDErr;
	nnt->LCDstep= LCDStep;


	
	//pour le test
//	n->loadVector("c:\\nabil test.txt");
	
	//conversion de Strig a *char
	if (newLoadVecteur){
		char file[200];
		for(int i=0;i< (int) (loadStylFile->length ()) ;i++)
			file[i] =(char) loadStylFile->ref(i);
		file[i] =0;
		n->loadVector(file);
		n->saveVector("patern.txt");
	}
	n->restNetwork();
	n->setVectorToNetwork();


	ButtonLearnInfo->setPixmap( *PixmapInLearn );
	//ButtonLearnInfo->repaint () ;

	
//	system("test.exe");//auto filter

	//if (!nnt->StopLearn)  nnt->launchLearn();
	
	
	a.nnt = nnt;
	a.monFormCourbe = monFormCourbe;
	a.start();

	//nnt->StopLearn=0;
      
	//ButtonLearnInfo->setPixmap( *PixmapLearnOk ); 
	//ButtonLearnInfo->repaint () ;

}

void ConnectWidget::avanceRobotAll()
{
	//elle avance le robot chaque  timetoAvance
	if (timer->isActive())
	{
		timer->stop ();
		ButtonGoStopRobot->setPixmap(* pixmapGoRobot );
	}
	else
	{
		ButtonGoStopRobot->setPixmap( *pixmapStopRobot );
		timer->start( robotMover->timetoAvance, false );  
	}
}
//
// Handles paint events for the connect widget.
//

void ConnectWidget::paintEvent( QPaintEvent * )
{
    QPainter paint( this );

	paint.setBrush(QBrush( yellow ));

	//draw obstacle
	envObstacle->drawIt(&paint);


/*	QPoint *pw;
		QPoint *pNextw;

		for ( pw=errorGraph->first(); pw != 0; pw=pNextw )
			if(pNextw=errorGraph->next()) 
			paint.drawLine(*pw,*pNextw);
		
*/


    if (stateMode==ModeLearn) 
	{
	  //dessine la Trajet
		paint.drawLine(  *pointMyFin,*pointMyDebut );// plot point	
		
		QPoint *p;
		QPoint *pNext;
		paint.setPen(darkCyan) ;
		for ( p=path->first(); p != 0; p=pNext ){
			if(pNext=path->next()) 
				paint.drawLine(*p,*pNext);
		}
		
	
	  //draw the chouba robot in mode learn
	  if (path->last ()) robotMover->drawPrime(&paint,*path->last());
	}
	if (stateMode==ModeProbg) {
		robotMover->draw(&paint);
	}

	if (stateMode==ModeDrawObstcle) {
		paint.fillRect (PHautGauche->x(),PHautGauche->y(),
						PBasDroit->x() - PHautGauche->x(),
						PBasDroit->y() - PHautGauche->y(),
						QBrush( colors[9] ));
		robotMover->draw(&paint);
	}
	  
	
}
void ConnectWidget::drawObstacleMode(){stateMode=ModeDrawObstcle;}
void  ConnectWidget::AfficheRobot(){


	QPoint *pNext,*p;

	pNext= path->last () ;
	p =path->prev () ;

	if (p && pNext)
	{
	//elle doit contenir 2 element enmois
	   		
		  robotMover->CurentPosition = *p;

		  robotMover->CurentRotation = asin(((p->y()-pNext->y())/robotMover->getDistance(*p,*pNext)))/3.141593*180;

		  if ((pNext->x() - p->x())>0) 
		  {
			  if (robotMover->CurentRotation>0)
				   robotMover->CurentRotation=180-robotMover->CurentRotation;
			  else robotMover->CurentRotation=-180-robotMover->CurentRotation;

		  }

		  
	} 
}
void ConnectWidget::loadStyle(){
 loadStylFile = new QString(QFileDialog::getOpenFileName( "monstyle.txt", "*.*", this ));  
 	
	 newLoadVecteur=false;
	//conversion de Strig a *char
	char file[200];
	for(int i=0;i< (int) (loadStylFile->length ()) ;i++)
		file[i] =(char) loadStylFile->ref(i);
	file[i] =0;

	if (loadStylFile->length () >0 ){
		n->loadVector(file);
//		n->saveVector("patern.txt");
		n->restNetwork();
		n->setVectorToNetwork();
	}

}

void ConnectWidget::ButtonFilterF(){
	saveStylFile = new QString (QFileDialog::getSaveFileName( QString::null, "*.*", this ));
	if (saveStylFile->length () >0 )
		FilterFile();
	
}
void ConnectWidget::FilterFile(){
//conversion de Strig a *char
	char file[200];
	int i;

	file[0]='f';
	file[1]=' ';
	file[2]='"';


	for( i=0;i< (int) (saveStylFile->length ()) ;i++)
		file[i+3] =(char) saveStylFile->ref(i);

	file[i+3] ='"';
	file[i+4] =0;

	qWarning(file);
	system(file);

	
}
void ConnectWidget::saveTrajet(){

  saveStylFile = new QString (QFileDialog::getSaveFileName( QString::null, "*.*", this ));
  if (saveStylFile->length () >0 ){
	//conversion de Strig a *char
	char file[200];
	for(int i=0;i< (int) (saveStylFile->length ()) ;i++)
		file[i] =(char) saveStylFile->ref(i);
	file[i] =0;

	FILE *fp=fopen(file,"w");
	QPoint *pNext,*p,*testFirst;

	int count =0;

	for (QPoint *po=path->first();po;po = path->next())
		count++;
	QPoint *last =path->last();
	p =path->first();
	bool debut=true;
	testFirst=pNext= path->next();
	int prevRotation =0;
	
		 
	if (p && pNext )
	{
	//elle doit contenir 2 element enmois
	   
       while (pNext ) 
	   {
		  
		
		  robotMover->CurentPosition = *p;

		  prevRotation = robotMover->CurentRotation;

		  robotMover->CurentRotation = asin(((p->y()-pNext->y())/robotMover->getDistance(*p,*pNext)))/3.141593*180;

		  if ((pNext->x() - p->x())>0) 
		  {
			  if (robotMover->CurentRotation>0)
				   robotMover->CurentRotation=180-robotMover->CurentRotation;
			  else robotMover->CurentRotation=-180-robotMover->CurentRotation;

		  }
//pour ne pas avoire d'angle negative 
//c si la sortie du reseaux est entre 0 ->360
//		  if (robotMover->CurentRotation<0)
//				   robotMover->CurentRotation+=360;

		  if (testFirst==pNext){
				//architecture du resaeux
				fprintf(fp,"input %d\n",nnt->nbr_net[0]);
				for (int i=1;i<nnt->nbr_layer;i++)
				  fprintf(fp,"layer  %d\n",nnt->nbr_net[i]);
				fprintf(fp,"output %d\n",nnt->nbr_net[nnt->nbr_layer]);

				//nombre de patern
				fprintf(fp,"\nNBR_pat %d\n\n",count-2);
		  }


		  //la premier valeur est fausse
		  if (testFirst!=pNext){

			  if (!debut ) {
				  int Rots =0.0;
				  if ((robotMover->CurentRotation - prevRotation) > 180 ) Rots =-360;
				  if ((robotMover->CurentRotation - prevRotation) < -180 ) Rots =360;
				  float tmp =(float) (robotMover->CurentRotation - prevRotation + Rots + robotMover->MaxOngleForLearn ) /(robotMover->MaxOngleForLearn*2);
				  fprintf(fp,"%f",(float) (robotMover->CurentRotation - prevRotation + Rots + robotMover->MaxOngleForLearn ) /(robotMover->MaxOngleForLearn*2));
				  qWarning("rot=%d  =(cur:%d -prev:%d + robotMover->MaxOngleForLearn) 0= %f",(robotMover->CurentRotation - prevRotation+Rots  ),robotMover->CurentRotation,prevRotation,tmp);
			  }
			debut=false;

			

//la sortie est longle 0 ->360
//		  fprintf(fp,"%f",(float) robotMover->CurentRotation/360);

//xxxx
//ongle courant est donnner		  fprintf(fp,"\nIN_vect %f",(float)  robotMover->CurentRotation /360);
//ondonnepas  
			if ( last!=pNext) 
			{
			  fprintf(fp,"\nIN_vect ");
		  
			  for (int i=0;i<robotMover->nbrCapteur/2;i++)
			  {

				float cap0 = (float)  robotMover->getCapteurDistance(i,0)/500;
				if (cap0 >= 1.0) cap0=(float)0.999999; 
				float cap1 = (float)  robotMover->getCapteurDistance(i,0)/500;
				if (cap1 >= 1.0) cap1=(float)0.999999; 
				fprintf(fp,"%f %f ",
				  /*(float)  robotMover->getCapteurDistance(i,0)/500 ,
				  (float)  robotMover->getCapteurDistance(i,1)/500 );
				  */
				  cap0,cap1);
			  }

			  fprintf(fp,"\nOUT_vect ");
			}
		  }
		  p    = pNext;
		  pNext= path->next();
	   }
	} 
//	else
	fclose(fp);
	
	//on filtre desque on fait la sauvgarde
	FilterFile();

	//on met le ficher a faire loader le meme ficher
	loadStylFile = new QString(*saveStylFile);  
	newLoadVecteur=true;
  }
}

void ConnectWidget::avanceRobot(){

//robotMover->nbrCapteur
		  float testPattern  [9] ;
//l ongle ne entre pas ou net
//		  testPattern [0] = robotMover->CurentRotation /360;
//		  int cont = 1;

//ondonnepas		 
		  int cont = 0;

		  for (int i=0;i<robotMover->nbrCapteur/2;i++)
		  {
			  //input must be in [1,0]
			  float cap0= (float)  robotMover->getCapteurDistance(i,0)/500 ;
			  float cap1= (float)  robotMover->getCapteurDistance(i,1)/500 ;
			  
			  if (cap0 > 1.0 ) cap0 =1.0;
			  if (cap1 > 1.0 ) cap1 =1.0;

			  testPattern[cont++]	 =cap0;
			  testPattern[cont++]	 =cap1;
			/*testPattern[cont++]	 = (float)  robotMover->getCapteurDistance(i,0)/500 ;
			testPattern[cont++] = (float)  robotMover->getCapteurDistance(i,1)/500 ;*/

		  }
			

//		  QMessageBox::information( this, "obstacle","The factory default will be used instead." );

		   
		//  robotMover->CurentRotation = nnt->getResulta(testPattern)*360 ;
		int temp = robotMover->CurentRotation;
		
		mutex->lock();
		robotMover->rotate((nnt->getResulta(testPattern)*(robotMover->MaxOngleForExec*2))-robotMover->MaxOngleForExec);
		mutex->unlock();


		qWarning("rot=%d",((int)(nnt->getResulta(testPattern)*(robotMover->MaxOngleForExec*2))-robotMover->MaxOngleForExec));
		
		
		//test si le resulata provoque une colesion
		 
		QString s;
		int rot=0;
		
		
		if (OnLineLearn && (robotMover->getCapteurDistance(0,1) <robotMover->ImpactDistance))//33
		{
			//	QMessageBox::information( this, "obstacle","learn ok");
		    robotMover->CurentRotation = temp ;
			
/*			if  (robotMover->getCapteurDistance(2,0)>11) rot=-90; // °45
			if  (robotMover->getCapteurDistance(2,1)>11) rot=90; // °45
			if  (robotMover->getCapteurDistance(1,1)>11) rot=45; // °45
			if  (robotMover->getCapteurDistance(3,0)>11) rot=-45; // °45
		//	if  (robotMover->getCapteurDistance(0,1)>11) rot=0; // °45
		//	QMessageBox::information( this, "obstacle",
		//	s.arg ( (int) (nnt->getResulta(testPattern)*360)-180 , 10, 10 )) ;
		//	s.arg ( rot, 10, 10 )) ;
*/
			
			
			int m90 = robotMover->getCapteurDistance(2,0);
			int p90 = robotMover->getCapteurDistance(2,1);
			
			int p45 = robotMover->getCapteurDistance(1,1);
			int m45 = robotMover->getCapteurDistance(3,0);

			
			int sensRot=0;

			if (robotMover->prevRot>0)	sensRot++; else sensRot--; 
			if (p45<m45)				sensRot--; else sensRot++; 
			if (p45+p90 < m45+m90)		sensRot--; else sensRot++; 

			
			if (sensRot>0) rot = robotMover->MaxOngleForExec ;else rot = -robotMover->MaxOngleForExec ;
			
			rot/=6;

			robotMover->CurentRotation=(rot)+temp;
			vecteur *v=new vecteur(8,1);

			int cont =0;
			for (int i=0;i<robotMover->nbrCapteur/2;i++)
			{
			  v->in[cont++]	 = (float)  robotMover->getCapteurDistance(i,0)/500 ;
			  v->in[cont++] = (float)  robotMover->getCapteurDistance(i,1)/500 ;
			}

			v->out[0]=(rot+robotMover->MaxOngleForExec)/(robotMover->MaxOngleForExec*2);
			int rotavant =((int)(nnt->getResulta(testPattern)*(robotMover->MaxOngleForExec*2)))-robotMover->MaxOngleForExec;
			
			n->addvect(v);
		
			n->restNetwork();
				
			n->setVectorToNetwork();
	
  			
			ButtonLearnInfo->setPixmap( *PixmapInLearn );
			ButtonLearnInfo->repaint () ;

			
			
			//save les nouveux patern du learn
			/*n->saveVector("newPatern.txt");
			system("test.exe");
			n->loadVector("nabil test.txt");
			n->restNetwork();
			n->setVectorToNetwork();
*/
			mutex->lock();
			nnt->launchLearn();
			mutex->unlock();
			
			ButtonLearnInfo->setPixmap( *PixmapLearnOk ); 
			ButtonLearnInfo->repaint () ;

			
			qWarning("apres(learn) rot=%d in %d",rot,((int)(nnt->getResulta(testPattern)*(robotMover->MaxOngleForExec*2)))-robotMover->MaxOngleForExec);
			qWarning("avant (learn) rot=%d",rotavant);
		

		}

		//update data robot

		if (robotMover->getCapteurDistance(0,1) >11)
		   robotMover->move(robotMover->destanceToAvance);
		else 
		{
		//	robotMover->move(-20);
			QApplication::beep ();
			if (rot) robotMover->CurentRotation+=60;
			else robotMover->CurentRotation-=60;

		}

		robotMover->prevRot=rot;
/*
		   	qWarning("(3,0)=%d",robotMover->getCapteurDistance(3,0));
			qWarning("(3,1)=%d",robotMover->getCapteurDistance(3,1));
			qWarning("(2,0)=%d",robotMover->getCapteurDistance(2,0));
			qWarning("(2,1)=%d",robotMover->getCapteurDistance(2,1));
			qWarning("(1,1)=%d",robotMover->getCapteurDistance(1,1));
			qWarning("(0,1)=%d",robotMover->getCapteurDistance(0,1));
*/		


		update();
		 

}

//
// Handles mouse press events for the connect widget.
//

void ConnectWidget::mousePressEvent( QMouseEvent * e)
{
	if (stateMode==ModeLearn) 
	{	
		if (path->isEmpty ()) 	
			path->append (new QPoint(e->pos()));
		*pointMyDebut = e->pos();
	}
	
	*PHautGauche =e->pos();
}

//
// Handles mouse release events for the connect widget.
//

void ConnectWidget::mouseReleaseEvent( QMouseEvent *e )
{
	*pointMyFin = e->pos();	
	*PBasDroit   =e->pos();

	if (stateMode==ModeLearn) 
	{	
		path->append (new QPoint(e->pos()));
		AfficheRobot();
	} 
	
	if (stateMode==ModeProbg)  robotMover->CurentPosition = e->pos();
	
	if (stateMode==ModeDrawObstcle) envObstacle->addObstacle(new obstacle(*PHautGauche,*PBasDroit));

	update();
}

//
// Handles mouse move events for the connect widget.
//

void ConnectWidget::mouseMoveEvent( QMouseEvent *e )
{
	   *PBasDroit   =e->pos();
	    if (stateMode==ModeDrawObstcle) update();	
}


ConnectWidget::~ConnectWidget()
	{
	monFormCourbe->hide ();
			//kill thread !!!
	a.endExec = true;
	while (a.running ()) ;
		qWarning("alll mort");
	}

//
// Create and display a ConnectWidget.
//

int main( int argc, char **argv )
{
	mutex = new QMutex;
    QApplication app( argc, argv );
    ConnectWidget connect;
	
	
    app.setMainWidget( &connect );
	app.setName( ( "ANN ML for avoiding obstacl (N°380)" ) );
    connect.show();
	



     return app.exec();
//    delete mutex;	
}
