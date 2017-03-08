
/*******************************************************************************************
/*		cette version traite le fixed point avec les parametre MontiBit,ExpoBit
/*		et represente le nombre de dit avant et apre la vergule
/*		realiser par n38
/*
/*
/*
/*******************************************************************************************/





#include "FixedPoint.h"

int  FixedPoint::ExpoBit=15;
int  FixedPoint::MontiBit=15;

long FixedPoint::exp2(char i)
{
	long res=1;
	if (i>0)
	  while(i--)
		res*=2;
	else 
	    while(i++)
		res/=2;	

	return(res);
}


/*****************************************************************************************
/   affiche le fixed point en format binaire 
/*****************************************************************************************/

void FixedPoint::showPropBin(){

	char bin[36];

	_itoa(this->NSource,bin,2);//bin[32]=0;

	printf("\nbinaire format :\nNbr[%d] fixed point =[%s]",NSource,bin );
}


/*****************************************************************************************
/   transforme  le fixed point en nombre enter qui le represente NSource
/*****************************************************************************************/

FixedPoint::FixedPoint(float source){

	//enregistre la source pour les verification du debugage
	fSource=source;
    
	//traitement de signe
	if (source >=0) bitSig =1;
	else {bitSig =-1;source*=-1;}
	
   //gestion du debordement de exp
	if (((int) source)> exp2(ExpoBit)-1){
		
       if (degMode) printf("\ndebordement %f",source);
	   NSource =exp2(ExpoBit+MontiBit)-1;
	}
    else  NSource= (long) (source*exp2(MontiBit));

   if (degMode) printf("\ncnvesion:exp[%f]= real[%f]",getFolat(),fSource);
	 
}


/*****************************************************************************************
/   retune la FLOAT  qui le represente NSource
/*****************************************************************************************/

float FixedPoint::getFolat()
{
  return ( bitSig *((float) NSource)/exp2(MontiBit));
}


/*****************************************************************************************
/   operateur - defini apartire du +
/*****************************************************************************************/

FixedPoint FixedPoint::operator- (FixedPoint f1)
{
	return (this->operator+ (FixedPoint (f1.NSource  ,- f1.bitSig )));
}


/*****************************************************************************************
/    operateur +
/*****************************************************************************************/

FixedPoint FixedPoint::operator+ (FixedPoint f1)
{
  // affichage pour le debugage
  if (degMode) printf("\nCPU :fs1[%f]+fs2[%f]=%f",
	  this->fSource,f1.fSource,( this->fSource)+( f1.fSource));

  long result=(bitSig*NSource)+ (f1.bitSig *f1.NSource);
  
  //gestion du signe du resulat
  char bitSigresult=1;
  if (result <0) {
	 bitSigresult=-1;
	 result*=-1;
  }

  //debordement (valeur infini)
  if (result >=exp2(ExpoBit+MontiBit))
	  result= exp2(ExpoBit+MontiBit)-1;
     
  FixedPoint res(result,bitSigresult);

  // affichage pour le debugage
  if (degMode) printf("\nEXP :fs1[%f]+fs2[%f]=%f",this->getFolat(),f1.getFolat(),res.getFolat());
  if (degMode==2) if  ((res.getFolat() -this->fSource-f1.fSource)>DelateRRO) getchar();

 return (res);
}


/*****************************************************************************************
/    operateur *
/*****************************************************************************************/

FixedPoint FixedPoint::operator* (FixedPoint f1)
{
  // affichage pour le debugage
  if (degMode) printf("\nCPU :fs1[%f]*fs2[%f]=%f",
	  this->fSource,f1.fSource,this->fSource*f1.fSource);
    unsigned long result;  
  if (TypeBufferResst==0){

    //sinon elle deborde lors de *
    if (MontiBit%2==0)
      result = (NSource/exp2(MontiBit/2)) * (f1.NSource/exp2(MontiBit/2));
    else 
      result = (NSource/exp2((MontiBit/2)+1)) * (f1.NSource/exp2(MontiBit/2));
  }
else 
{
	 result=(NSource)* ( f1.NSource);
    result/=exp2(MontiBit);//car 1.001*1.01=1.00001
}

//deteroration prisision (apre la vergule) du resulta
// result/=exp2(MontiBit);//car 1.001*1.01=1.00001
 
 //debordement (valeur infini)
 if (result >=exp2(ExpoBit+MontiBit))
	 result= exp2(ExpoBit+MontiBit)-1;
  
 FixedPoint res(result,f1.bitSig *bitSig);

  // affichage pour le debugage
 if (degMode) printf("\nEXP :fs1[%f]*fs2[%f]=%f",this->getFolat(),f1.getFolat(),res.getFolat());
 if (degMode==2) if  ((res.getFolat() -(this->fSource*f1.fSource))>DelateRRO) getchar();
 return (res);
 
}
 


