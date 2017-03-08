#ifndef net_included
#define net_included

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <qlist.H>
#include <qapplication.h> 
#include "obstacle.h"
#include "Robot.h"
#include <qlcdnumber.h>



#include  "network.h"


class vecteur
{
public:
	float *in,*out;
	int nbrIN,nbrOut;

	vecteur(vecteur *v);
	vecteur(int In,int Out);
};


class net
{
public :
	bool load;
	networkFather *usedNetWork;
	
	QList<vecteur> *vect;
	int nbr_pattern;

	net();
	
	addvect(vecteur *v);//les donner des capteur et la valeur du rotation optionel
	
	loadVector(char *fileName);
	saveVector(char *fileName);
	setVectorToNetwork();
	restNetwork();

};
#endif




