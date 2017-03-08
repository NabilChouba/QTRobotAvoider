
#include "enveronement.h"

void enverenement::addObstacle(obstacle *obst)
{
	ensembleObstacle->append (obst);
}
enverenement::enverenement()
{
	ensembleObstacle = new QList<obstacle>();
	visible=true;
}

void enverenement::rest()
{
	delete ensembleObstacle;
	ensembleObstacle = new QList<obstacle>();
}
void enverenement::drawIt(QPainter *paint)
{
	if (visible)
	{
	  
	  obstacle *ob;

	  for ( ob=ensembleObstacle->first(); ob != 0; ob=ensembleObstacle->next() )
	  {
		
		paint->fillRect (ob->min.x(),ob->min.y(),
						ob->max.x() - ob->min.x(),
						ob->max.y() - ob->min.y(),
						QBrush( Qt::darkCyan));		
	  }
	}
}
void enverenement::load(char *file)
{
	rest();
	
	FILE * fp= fopen(file,"r");
	char ligne [100];
	int minx,miny,maxx,maxy;
	while (fgets(ligne,80,fp)) 
	{
		
		if (sscanf(ligne,"%d %d %d %d\n",&minx,&miny,&maxx,&maxy)!=-1){
		  obstacle *ob=new obstacle(QPoint(minx,miny),QPoint(maxx,maxy));
		  addObstacle(ob);
		}
	}
	fclose(fp);
}
void enverenement::save(char *file)
{
	obstacle *ob;
	FILE * fp= fopen(file,"w");
	if (fp){
	  for ( ob=ensembleObstacle->first(); ob != 0; ob=ensembleObstacle->next() )
	    fprintf(fp,"%d %d %d %d\n",ob->min.x(),ob->min.y(),ob->max.x(),ob->max.y());
	}
	fclose(fp);
}