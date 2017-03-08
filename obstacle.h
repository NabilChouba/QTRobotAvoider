#ifndef obstacle_included
#define obstacle_included
#include <qPoint.h>

//#define cof 40
//#define org 170

#define cof 1
#define org 0

class obstacle {
public:
	QPoint min,max;
	obstacle (QPoint min0,QPoint max0): max( (max0)*cof),min( (min0)*cof){add();};	
	obstacle (){};
	void add(){
		min.setX(min.x()+org);
		min.setY(min.y()+org);
		max.setX(max.x()+org);
		max.setY(max.y()+org);
	}

};

#endif