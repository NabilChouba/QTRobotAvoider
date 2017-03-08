#ifndef enverenement_included
#define enverenement_included
#include "obstacle.h"
#include <qpainter.h>
#include <qlist.H>
#include <QColor.h>
#include <stdio.h>


class enverenement 
{
  public :

	enverenement();
	bool visible;
	void inversVisibliter(){visible=!visible;};
	QList<obstacle> *ensembleObstacle;
	void load(char *file);
	void save(char *file);
	void addObstacle(obstacle *obst);
	void drawIt(QPainter *paint);
	void rest();

};

#endif
