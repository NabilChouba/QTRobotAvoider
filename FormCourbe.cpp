// FormCourbe.cpp: implementation of the FormCourbe class.
//
//////////////////////////////////////////////////////////////////////

#include "FormCourbe.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




FormCourbe::FormCourbe( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
	Xscals=1.0;
	curentGraph=0;
	scaled =false;
	dx=-0;

	zoomPlus = new QPushButton( this, "zoomPlus" );
    zoomPlus->setGeometry( QRect( 320, 20, 40, 41 )); 
    zoomPlus->setText( tr( "Zoom +" ) );
	/*zoomPlus->setPixmap(* pixmapSaveW );*/

	zoomMoin = new QPushButton( this, "zoomMoin" );
    zoomMoin->setGeometry( QRect( 360, 20, 40, 41 )); 
    zoomMoin->setText( tr( "Zoom -" ) );

	clearAllCourbe = new QPushButton( this, "Clear" );
    clearAllCourbe->setGeometry( QRect( 440, 20, 40, 41 )); 
    clearAllCourbe->setText( tr( "Clear" ) );

	TranslatePlus = new QPushButton( this, "TranslatePlus" );
    TranslatePlus->setGeometry( QRect( 400, 20, 40, 41 )); 
    TranslatePlus->setText( tr( "->" ) );

	TranslateMoin = new QPushButton( this, "TranslateMoin" );
    TranslateMoin->setGeometry( QRect( 280, 20, 40, 41 )); 
    TranslateMoin->setText( tr( "<-" ) );


	connect( zoomPlus, SIGNAL(clicked()),this  , SLOT(funZoomPlus()) );
	connect( zoomMoin, SIGNAL(clicked()),this  , SLOT(funZoomMoin()) );
	connect( clearAllCourbe, SIGNAL(clicked()),this  , SLOT(funclearAllCourbe()) );
	connect( TranslateMoin, SIGNAL(clicked()),this  , SLOT(funTranslateMoin()) );
	connect( TranslatePlus, SIGNAL(clicked()),this  , SLOT(funTranslatePlus()) );


}

void FormCourbe::courbeDraw(  )
{

    QPainter paints( this );

	if (paints.isActive()  ) {

	int gradWidth=20;
	int gradHeight=20;
	int bordWidth=60;
	int bordHeight=60;
	
	//paints.drawRect (bordWidth ,bordHeight,this->width()-bordWidth*2,this->height()-bordHeight*2);
	paints.setViewport (bordWidth ,bordHeight,this->width()-bordWidth*2,this->height()-bordHeight*2);
	paints.scale (Xscals,1);
	paints.translate (dx,0);

	QPoint *pw;
	QPoint *pNextw;

	paints.setPen(Qt::green);
	
	QColor *colors = new QColor[20];
	
	colors[1] = Qt::blue;
	colors[0] = Qt::red;
	colors[2] = Qt::white;
	colors[3] = Qt::yellow;
	colors[4] = Qt::magenta;
	colors[5] =  QColor(10,0,89);
	colors[6] =  QColor(0,46,89);
	colors[7] =  QColor(110,45,189);
	colors[8] =  QColor(0,0,189);
	colors[9] =  QColor(210,200,89);

	QList<QPoint> *errorGraph=TabErrorGraph[curentGraph-1];
	paints.setPen(colors[curentGraph-1]);	

	pNextw=errorGraph->last();
	pw=errorGraph->prev();

		if (pw->x()/20 >-dx ) 
		paints.drawLine(pw->x()/20,this->height()-pw->y()*this->height()/10000,pNextw->x()/20,this->height()-pNextw->y()*this->height()/10000 );
		//             step
	}
}
void FormCourbe::paintEvent( QPaintEvent * )
{
    QPainter paint( this );

	paint.begin(NULL) ;
	paint.setBrush(QBrush( black ));
	paint.setPen(Qt::darkGreen);

	int gradWidth=20;
	int gradHeight=20;
	int bordWidth=60;
	int bordHeight=60;

	
	paint.drawRect (bordWidth ,bordHeight,this->width()-bordWidth*2,this->height()-bordHeight*2);
	paint.setViewport (bordWidth ,bordHeight,this->width()-bordWidth*2,this->height()-bordHeight*2);


	
	

    paint.setFont( QFont(  "courier", 12 ) );
       
	for(int j=0;j<=gradHeight;j++){
	  paint.drawLine (0,this->height()*(j)/gradHeight,this->width(), this->height()*(j)/gradHeight );
	  paint.setPen(Qt::darkYellow);
	  if (j!= gradHeight) paint.drawText (-46,this->height()*(j)/gradHeight,QString::number((double) (this->height()-this->height()*(j)/gradHeight )/this->height(),'g',3));
	  paint.setPen(Qt::darkGreen);
	}
	 
	

	paint.scale (Xscals,1);
	paint.translate (dx,0);
	
	paint.setFont( QFont(  "courier", 14) );

	int addone=-dx/gradWidth;
	gradWidth=gradWidth/Xscals;

	
	
	if (addone<0) addone=0;

	for(int i=0;i<=gradWidth+addone;i++){

	 if (this->width()/Xscals*(i)/gradWidth >-dx && this->width()/Xscals*(i)/gradWidth +dx <this->width()/Xscals) {
	  //print echell step

	  if (1/Xscals <1 || (Xscals>0 && (! (i%int (1/Xscals))))){

		  
		  
		paint.drawLine (this->width()/Xscals*(i)/gradWidth,0,this->width()/Xscals*(i)/gradWidth,this->height());
	    
		paint.save();
	    paint.translate (int (((this->width()*(i)/gradWidth)/Xscals)-10),int(this->height()+10));
	    paint.rotate (90);
	    paint.setPen(Qt::darkYellow);
	    //paint.drawText ((this->width()*(i)/gradWidth)-10,this->height()+10,QString::number((this->width()*(i)/gradWidth)*20));
	    paint.scale (1,1/Xscals);
		paint.drawText (0,0,QString::number(((this->width()*(i)/Xscals)/gradWidth)*20));
		//paint.drawText (0,0,QString::number(i));
		paint.scale (1,Xscals);
	    paint.restore();
		paint.setPen(Qt::darkGreen);  
		  
	  }
	  else
	  {
		  
		  paint.save();
		  paint.setPen(QColor (0,70,0));
		  paint.drawLine (this->width()/Xscals*(i)/gradWidth,0,this->width()/Xscals*(i)/gradWidth,this->height());
		  paint.restore();
	  }
	}
	}

	QPoint *pw;
	QPoint *pNextw;

	paint.setPen(Qt::green);
	
	QColor *colors = new QColor[20];
	
	colors[0] = Qt::blue;
	colors[1] = Qt::red;
	colors[2] = Qt::white;
	colors[3] = Qt::yellow;
	colors[4] = Qt::magenta;
	colors[5] = Qt::cyan;

	colors[6] = Qt::darkBlue;
	colors[7] = Qt::darkRed;
	colors[8] = Qt::darkYellow;
	colors[9] = Qt::darkMagenta;
	colors[10] = Qt::darkCyan;


	//if (TabErrorGraph[curentGraph-1] && TabErrorGraph[curentGraph-1]->last() )
	//paint.translate  (TabErrorGraph[curentGraph-1]->last()->y()*this->height()/20000,0);
	//float ip=TabErrorGraph[curentGraph-1]->last()->y();


	for(int k=0;k<curentGraph;k++) {
	QList<QPoint> *errorGraph=TabErrorGraph[k];
paint.setPen(colors[k]);	
	pw=pNextw=NULL;
	for ( pw=errorGraph->first(); pw != 0; pw=pNextw ){
		if(pNextw=errorGraph->next()) 
		if (pw->x()/20 >-dx && pw->x()/20 +dx <this->width()/Xscals) 
		paint.drawLine(pw->x()/20,this->height()-pw->y()*this->height()/10000,pNextw->x()/20,this->height()-pNextw->y()*this->height()/10000 );
		//             step
	}
	
	}
	paint.end() ;
}

void FormCourbe::funZoomPlus(){
		Xscals*=2;
		repaint();
		scaled = true;

	}
void FormCourbe::funZoomMoin(){
		Xscals/=2;
		repaint();
		scaled = true;
	}
void FormCourbe::funclearAllCourbe(){
	for(int k=0;k<curentGraph;k++) 
		delete(TabErrorGraph[k]);
	
	curentGraph=0;
	repaint();
		
}
void FormCourbe::funTranslatePlus(){
		dx-=50;
		repaint();
		
	}
void FormCourbe::funTranslateMoin(){
		dx+=50;
		repaint();
		
	}
