#include "robot.h"
#include <math.h>


//donne la distance du robot % aux point p
float Robot::getDistance(QPoint deb,QPoint end){
	return (float) sqrt ((deb.x() - end.x()) * (deb.x() - end.x()) + (deb.y() - end.y()) * (deb.y() - end.y()) );
}

//faire une rotation degree du robot
void Robot::rotate(int degree){
	CurentRotation+=degree ;
	CurentRotation=CurentRotation % 360;
//	printf("new rotat\t");getInfo();
}

//deplase le robot +distance 
void Robot::move(int distance){
	CurentPosition.setX(CurentPosition.x() + (int) (cos(this->CurentRotation*3.141593/180) * distance));
	CurentPosition.setY(CurentPosition.y() + (int) (sin(this->CurentRotation*3.141593/180) * distance));
	
//	printf("new Move\t");getInfo();
	
}

int Robot::getCapteurDistance(int numCapter,int Sens){
	
	//droite portant le chanp de vision du capteur 
	// y =   tang(ongle) x + b
	// b = y-tang(ongle) x
	// d'out 
	// y =   tan(CurentRotation) x + CurentPosition.y - tang(ongle) CurentPosition.x
	//

	//cas d'un obstacle
	// intersection avec un obstacle
	// obstacle(xmim,ymin) (xmax,ymax)
	
	// 4 point d'intersection
	// on choisit qui satisfier les condition suivant 
	//
	//  1: xmin < x < xmax
	//  2: ymin < y < ymax
	//  3: le plus pres du robot 
	
	// xmin, tan(CurentRotation) xmin + CurentPosition.y - tang(ongle) CurentPosition.x
	// xmax, tan(CurentRotation) xmax + CurentPosition.y - tang(ongle) CurentPosition.x
	// (ymin - CurentPosition.y + tang(ongle) CurentPosition.x )/ tan(CurentRotation) ,ymin
	// (ymax - CurentPosition.y + tang(ongle) CurentPosition.x )/ tan(CurentRotation) ,ymax
	
	//generalisation
	//il faut prendre enconsederation que le lobstacle le plus pres

//Debut Algorithme
	//pour un capteur --> distancePositif ,distanceNegatif

	//calcule du vecteur pour trouver le sens

	

	double CateurCurentRotation = CurentRotation + (360/(nbrCapteur)) * numCapter ;
	
	 float senspositif_x= (float) CurentPosition.x() + (float) (10*cos(CateurCurentRotation*3.141593/180) );
	 float senspositif_y= (float) CurentPosition.y() + (float) (10*sin(CateurCurentRotation*3.141593/180) );


	float distPositif = 99999.;int solPositif  = -1;
	float distNigatif = 99999.;int solNigatif  = -1;
	float delta =0.1f;
	
	float sens;

	//pour chaque obstacle
	for ( obstacle *obst=envrnemt->first(); obst != 0; obst=envrnemt->next() ){
	// for (int k=0;k<nbreObstacle;k++){
		QPoint *p[4];
		p[0]=new QPoint( obst->min.x() , tan(CateurCurentRotation*3.141593/180) * obst->min.x() + CurentPosition.y() - tan(CateurCurentRotation*3.141593/180) * CurentPosition.x());
		p[1]=new QPoint( obst->max.x() , tan(CateurCurentRotation*3.141593/180) * obst->max.x() + CurentPosition.y() - tan(CateurCurentRotation*3.141593/180) * CurentPosition.x());
		p[2]=new QPoint((obst->min.y() - CurentPosition.y() + tan(CateurCurentRotation*3.141593/180) * CurentPosition.x() )/ tan(CateurCurentRotation*3.141593/180) ,obst->min.y());
		p[3]=new QPoint((obst->max.y() - CurentPosition.y() + tan(CateurCurentRotation*3.141593/180) * CurentPosition.x() )/ tan(CateurCurentRotation*3.141593/180) ,obst->max.y());
		
		float dist = 99999.;	
	    int sol  = -1;

		//pour chaque droite du obstacle
		for (int i=0;i<4;i++){
			
		//	printf("point sol (%f,%f) dist =%f\n",p[i]->x,p[i]->y,p[i]->getDistance(Point (CurentPosition.x,CurentPosition.y)));
			if ((((obst->min.y()-delta <=p[i]->y())) && (p[i]->y() <= (obst->max.y() +delta))) &&
				(((obst->min.x()-delta) <=p[i]->x()) && (p[i]->x() <= (obst->max.x() +delta))) )
			{	
				//choisir la plus proche des intersection
				if ((dist >= getDistance(*p[i],QPoint ( CurentPosition.x(), CurentPosition.y())))
					&& (getDistance(*p[i],QPoint (CurentPosition.x(),CurentPosition.y())) >=0.001))
				{
					sol  = i;
					dist = getDistance(*p[i],QPoint (CurentPosition.x(),CurentPosition.y()));
				}
			}
		}

		//si existe une solution
		if (sol>=0){

		  sens = (senspositif_x - CurentPosition.x()) *(p[sol]->x() - CurentPosition.x()) 
			    +(senspositif_y - CurentPosition.y()) *(p[sol]->y() - CurentPosition.y()) ;
		 if (sens==0) 
			 sol=0;
		  if (sens>0) {
			  if (dist < distPositif){
				//solPositif =k;
				distPositif =dist;
			  }
		//	  printf(" sens +");
			 
		  }
		  else {
			  if (dist < distNigatif){
				//solNigatif =k; 
				distNigatif =dist;
			  }
		//	  printf(" sens -");
			 
		  }
		  //printf(" obstacle %d la solution [%d] distance=%f \n",k+1,sol,dist);
		}
	//	else 
		  //printf(" obstacle %d pas dintersection \n",k+1);
	}

		  
	    // printf(" obstacle %d  distance=+ %f \n",solPositif+1,distPositif);
		// printf(" obstacle %d  distance=- %f \n",solNigatif+1,distNigatif);

	if (Sens) return distPositif;
	else  return distNigatif;
}

void Robot::getInfo(){
	
//	printf("Robot pos init = (%f,%f) rot init = %d \n",CurentPosition.x,CurentPosition.y, CurentRotation);
}
void Robot::draw(QPainter *paint){
	//draw la cercle qui represente le robot
	paint->drawEllipse (CurentPosition.x()-10,CurentPosition.y()-10,20,20);
    
	//draw l ongle q fait le robot avec l horisant
	paint->setPen(Qt::black); 
	QString	sCurentRotation(QString::number(CurentRotation));
	paint->translate(CurentPosition.x(),CurentPosition.y());
	paint->setFont( QFont( "courier", 14, QFont::Bold ) );
	paint->drawText ( -5, 0,sCurentRotation ,sCurentRotation.length ()  ) ;
	paint->setFont( QFont( "courier", 10, QFont::Bold ) );
	

	//on draw les info(distance) et les line des capteur
	double CateurCurentRotation;
    int Distance;
    QString *sDistance;
	
	paint->resetXForm ();
    for (int i=0;i<(nbrCapteur/2);i++)
	{
		//mise a jour le repaire
	  CateurCurentRotation = CurentRotation + (360/(nbrCapteur)) * i ;
	  paint->translate(CurentPosition.x(),CurentPosition.y());
	  paint->rotate (  CateurCurentRotation );

	  //traitement de 2  capteur qui sont sur la meme droite
	  for(int sens=0 ;sens<2;sens++)
	  {
		if (sens % 2){
		  Distance  = getCapteurDistance(i,1);
	      sDistance = new QString(QString::number(Distance));
		}
		else {
		  Distance  = -getCapteurDistance(i,0);
	      sDistance = new QString(QString::number(-Distance));
		 }

		//draw le line du capteur
		paint->setPen(Qt::black) ;
		paint->setPen(Qt::DashLine);
		
		if (sens==1 && i==0) paint->setPen(Qt::green) ;//affiche le devant en green
		paint->drawLine(  QPoint(0,0),QPoint (Distance,0));

		//draw le text qui represente la distance entre le robo et l'obstacle
		paint->setPen(Qt::red) ;
		paint->drawText ( Distance/2, 0,*sDistance ,sDistance->length ()  ) ;

	  }
	  paint->resetXForm ();
	}
}
void Robot::drawPrime(QPainter *paint,QPoint next){

	QPoint temp=CurentPosition;
	CurentPosition=next;


	//draw la cercle qui represente le robot
	paint->drawEllipse (CurentPosition.x()-10,CurentPosition.y()-10,20,20);
    
	//draw l ongle q fait le robot avec l horisant
	paint->setPen(Qt::green); 
	QString	sCurentRotation(QString::number(CurentRotation));
	paint->translate(CurentPosition.x(),CurentPosition.y());
	paint->setFont( QFont( "courier", 14, QFont::Bold ) );
	paint->drawText ( -5, 0,sCurentRotation ,sCurentRotation.length ()  ) ;
	paint->setFont( QFont( "courier", 10, QFont::Bold ) );
	

	//on draw les info(distance) et les line des capteur
	double CateurCurentRotation;
    int Distance;
    QString *sDistance;

	paint->resetXForm ();
    for (int i=0;i<(nbrCapteur/2);i++)
	{
		//mise a jour le repaire
	  CateurCurentRotation = CurentRotation + (360/(nbrCapteur)) * i ;
	  paint->translate(CurentPosition.x(),CurentPosition.y());
	  paint->rotate (  CateurCurentRotation );

	  //traitement de 2  capteur qui sont sur la meme droite
	  for(int sens=0 ;sens<2;sens++)
	  {
		if (sens % 2){
		  Distance  = getCapteurDistance(i,1);
	      sDistance = new QString(QString::number(Distance));
		}
		else {
		  Distance  = -getCapteurDistance(i,0);
	      sDistance = new QString(QString::number(-Distance));
		 }

		//draw le line du capteur
		paint->setPen(Qt::DashLine );
		paint->setPen(Qt::green) ;
		

		if (sens==0 && i==0) paint->setPen(Qt::red) ;//affiche le devant en green
			paint->drawLine(  QPoint(0,0),QPoint (Distance,0));


		//draw le text qui represente la distance entre le robo et l'obstacle
		paint->setPen(Qt::green) ;
		paint->drawText ( Distance/2, 0,*sDistance ,sDistance->length ()  ) ;

	  }
	  paint->resetXForm ();
	}

	CurentPosition=temp;
}