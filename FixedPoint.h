
/*******************************************************************************************
/*		cette version traite le fixed point avec les parametre MontiBit,ExpoBit
/*		et represente le nombre de dit avant et apre la vergule
/*		realiser par n38
/*
/*
/*
/*******************************************************************************************/

#ifndef FixedPoint_included
#define FixedPoint_included

#include <stdlib.h>
#include <stdio.h>


#define TypeBufferResst 1//0 on retresser avant de multiplier 
						  //	1.2122 *1.7899  -> 1.21 *1.78 4chiffre apre ,
						  //1 on supose que le buffer resulat est asser long
						  //on fait la * puis on retreser
							 
#define degMode   0 // 1 affiche le debogage
					// 2 faire une pousse getchar() si le resulta est D > DelateRRO

#define DelateRRO 0.01 //test valeur


class FixedPoint{

	   
public:

	static int MontiBit , ExpoBit ;

   float fSource;
   long  NSource;
   char bitSig;

   float getFolat();
  
   long exp2(char i);
   FixedPoint(float source=0.0);

 
   
   FixedPoint(long  NNSource,char NbitSig):NSource(NNSource),bitSig(NbitSig)
   {fSource=getFolat();};
   void showPropBin();

   
   FixedPoint operator+ (FixedPoint f1);
   FixedPoint operator- (FixedPoint f1);
   FixedPoint operator* (FixedPoint f1);
   operator float(){return getFolat();};
   int operator< (FixedPoint f1){return (this->getFolat() <f1.getFolat());};
   int operator> (FixedPoint f1){return (this->getFolat() >f1.getFolat());};
    
};

#endif