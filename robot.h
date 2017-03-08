#ifndef robot_included
#define robot_included

#include "obstacle.h"

#include <QList.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <QColor.h>




class Robot {
public:
	int prevRot;//juste pour test

	int	nbrCapteur ;
	int MaxOngleForLearn;
	int MaxOngleForExec;
	int timetoAvance;
	int destanceToAvance;
	int ImpactDistance;//pour le superviseur
	

	obstacle *obst[10];
	void drawPrime(QPainter *paint,QPoint next);
	QList<obstacle> *envrnemt;
	int		CurentRotation;
	QPoint	CurentPosition;
	
	

	int 	getCapteurDistance(int numCapter,int Sens);
	void	rotate(int degree);
	void	move(int distance);
	void	setObstacle(QList<obstacle> *envrnemt0){envrnemt=envrnemt0;};
	void    draw(QPainter *paint);
	Robot(QPoint	CurentPosition0,int CurentRotation0,int nbrCapteur0):CurentPosition(CurentPosition0),nbrCapteur(nbrCapteur0),CurentRotation(CurentRotation0){
		//printf("creation avec\t%d capteur ",nbrCapteur0); 
		getInfo();
		MaxOngleForLearn =90;
		MaxOngleForExec  =45;
	};
	void getInfo();
	float getDistance(QPoint deb,QPoint end);
};
#endif