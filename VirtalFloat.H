

/*******************************************************************************************
/*		cette version traite le floating point 
		avec les parametre MontiBit,ExpoBit
/*		qui sont genirique +- par define
/*		realiser par n38
/*
/*
/*
/*******************************************************************************************/


#ifndef VirtalFloat_included
#define VirtalFloat_included



#include <stdlib.h>
#include <stdio.h>

#ifndef degMode
  #define degMode   0 //affiche le debogage
#endif


class VirtalFloat{
public:
	static int  MontiBit,ExpoBit;
	float fSource;
    long exp;
	int bais;
	unsigned long mont;
    char bitSig;
	float exp21(char i);
   float getFolat();
   VirtalFloat(float source = 0.0);
   VirtalFloat(long  Nmont,long Nexp,char NbitSig);
   void perteMontice();
   void showProp();
   void showPropBin();
   VirtalFloat operator+ (VirtalFloat f1);
   VirtalFloat operator- (VirtalFloat f1);
   VirtalFloat operator* (VirtalFloat f1);
   operator float(){return getFolat();};
   int operator< (VirtalFloat f1){return (this->getFolat() <f1.getFolat());};
   int operator> (VirtalFloat f1){return (this->getFolat() >f1.getFolat());};
   
    
};

#endif