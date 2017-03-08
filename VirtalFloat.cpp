

/*******************************************************************************************
/*		cette version traite le floating point 
		avec les parametre MontiBit,ExpoBit
/*		qui sont genirique +- par define
/*		realiser par n38
/*
/*
/*
/*******************************************************************************************/



#include "VirtalFloat.H"

int  VirtalFloat::ExpoBit=4;
int  VirtalFloat::MontiBit=4;

float VirtalFloat::exp21(char i)
{
	float res=1;
	if (i>0)
	  while(i--)
		res*=2;
	else 
	    while(i++)
		res/=2;	

	return(res);
}


/*****************************************************************************************
/  par copy
/*****************************************************************************************/

VirtalFloat::VirtalFloat(long  Nmont,long Nexp,char NbitSig):exp(Nexp),mont(Nmont),bitSig(NbitSig)
   {
	  //calcule du baise du expossent 
	   bais=(int)exp21(ExpoBit-1)-1; 

	   perteMontice();
	   fSource=getFolat();
	   //gestion du ZeRRo
	   if (exp <0) {exp=0;mont=0;}
	   //gestion du infini
	   if (exp >exp21(ExpoBit)-1) {exp=(long)exp21(ExpoBit)-1;mont=1;}
   
   };
/*****************************************************************************************
/  perte de presision du au taille reduit de la montice
/*****************************************************************************************/

void VirtalFloat::perteMontice(){

   while (mont >= exp21(MontiBit))
	   mont/=2;
}
/*****************************************************************************************
/  affiche exposant et montice
/*****************************************************************************************/

void VirtalFloat::showProp(){

  printf("\nsig =[%d]exp=[ %d ] montice=[ %d ]",bitSig,exp ,mont );

}


/*****************************************************************************************
/   affiche exposant et montice en forme binaire IEEE-754
/*****************************************************************************************/

void VirtalFloat::showPropBin(){

	char bin1[33];char bin2[33];

	_itoa(mont,bin1,2);//bin[32]=0;
	_itoa(exp,bin2,2);

	printf("\nbinaire format :\nmont =[%s]\nexp=[%s]",bin1,bin2 );
}



/*****************************************************************************************
/   transforme  le FLoating point en expossant et montissa
/*****************************************************************************************/

VirtalFloat::VirtalFloat(float source){
/***** calcule la montioce et exp a partire du float source****/

  //calcule du baise du expossent 
  bais=(int)exp21(ExpoBit-1)-1; 

  fSource=source;
  
  //traite la 0 ZERRO
  if (source==0.0) {bitSig =1;exp=0;mont=0;}
  else 
  {
    //getion du signe
    if (source >0) bitSig =1;
	else if (source <0)  {bitSig =-1;source*=-1;}
	
   //calcule de l exp	
   if (source>1.0)
	   //1000.646
	   for (exp=bais;(source/2)>1.0 && exp <= exp21(ExpoBit)-1;exp++ )
		   source/=2;
   else 
	   //0.0004545
	   for (exp=bais;source<1.0 && exp >0;exp--)
		   source*=2;

	//mont=(source*8388608)-8388608;

    //on peux pas le representer <min representer il sera 0
    if (exp<0)  {bitSig =1;exp=0;mont=0;}
	else {
	  //calcule du montice
      mont=source*exp21(MontiBit-1);
	  
	  //perte info montice de taille qui ne suporte pas
	  perteMontice();

      // affichage pour le debugage
	  if (degMode) printf("\ncnvesion:exp[%f]= real[%f]",getFolat(),fSource);
	}

  }
}


/*****************************************************************************************
/   retune la FLOAT  qui le represente exp et la mont
/*****************************************************************************************/

float VirtalFloat::getFolat()
{
	
	if (exp<exp21(ExpoBit)-1)
	   return ( bitSig*exp21(exp-bais)* ((float) mont)/exp21(MontiBit-1));
	else return (0xFFFF);
}



/*****************************************************************************************
/   operateur - defini apartire du +
/*****************************************************************************************/

VirtalFloat VirtalFloat::operator- (VirtalFloat f1)
{
	return (this->operator+ (VirtalFloat (f1.mont ,f1.exp ,- f1.bitSig )));
}



/*****************************************************************************************
/    operateur +
/*****************************************************************************************/

VirtalFloat VirtalFloat::operator+ (VirtalFloat f1)
{
  // affichage pour le debugage
  if (degMode) printf("\nCPU :fs1[%f]+fs2[%f]=%f",
	  this->fSource,f1.fSource,(this->bitSig * this->fSource)+(f1.bitSig * f1.fSource));

  //gestion du ZERRO
  if ( this->exp<0) return ( VirtalFloat(f1.mont,f1.exp,f1.bitSig));
  if ( f1.exp<0) return ( VirtalFloat(this->mont,this->exp,this->bitSig));

  //gestion du infini
  if ((f1.exp>=exp21(ExpoBit)-1)||(this->exp>=exp21(ExpoBit)-1)) 
	  return (VirtalFloat(1,exp21(ExpoBit)-1,f1.bitSig));
 
  // metre les deux en meme exposant 
  VirtalFloat f2(*this);
  if (f1.exp<f2.exp ){
	  
		f1.mont /= exp21(f2.exp - f1.exp);
		f1.exp  += f2.exp -f1.exp;
  }
  else if (f2.exp<f1.exp ){

		f2.mont /= exp21(f1.exp-f2.exp);
		f2.exp  += f1.exp-f2.exp;
  }

 //adition des montice 
  long somme=(f1.bitSig * f1.mont) +( f2.bitSig *f2.mont);
 
  //gestion du bit de sign
   char singAdd=1;
   if ( somme<0 )  {singAdd=-1;somme*=-1;}

  //gestion du dubordement de la montissa  
  if (somme>=exp21(MontiBit-1)*2){
	VirtalFloat res(somme/2,f2.exp+1,singAdd);
	res.perteMontice();
		
	// affichage pour le debugage
    if (degMode)  printf("\nEXP :fs1[%f]+fs2[%f]=%f",this->getFolat(),f1.getFolat(),res.getFolat());
    if (degMode==2)  if  ((res.getFolat() -f2.fSource-f1.fSource)>0.0001) getchar();
	return (res);
  }
  else {
	 VirtalFloat res(somme,f2.exp,singAdd);
	 res.perteMontice();

	 // affichage pour le debugage
     if (degMode) printf("\nEXP :fs1[%f]+fs2[%f]=%f",this->getFolat(),f1.getFolat(),res.getFolat());
	 if (degMode==2) if  ((res.getFolat() -f2.fSource-f1.fSource)>0.0001) getchar();
	 return (res);
  }
}


/*****************************************************************************************
/    operateur *
/*****************************************************************************************/

VirtalFloat VirtalFloat::operator* (VirtalFloat f1)
{
   // affichage pour le debugage
  if (degMode) printf("\nCPU :fs1[%f]*fs2[%f]=%f",
	  this->fSource,f1.fSource,this->fSource*f1.fSource);

  //calcule de la mantissa
  long result=((double long )f1.mont*this->mont) /exp21(MontiBit-1);

  //gestion du infini	
  if (exp+f1.exp-bais>=exp21(ExpoBit)-1) 
	  return (VirtalFloat(1,exp21(ExpoBit)-1,f1.bitSig*bitSig));

   //gestion du Zerro
  if (exp+f1.exp-bais<0) {
	  // affichage pour le debugage
	  if (degMode) printf("\nEXP :ZEro faux depase exp<0");
	  return (VirtalFloat(1,0,0));
  }

  //gestion du dubordement de la montissa
  if (result < exp21(MontiBit-1)*2) {
	 VirtalFloat res(result,exp+f1.exp-bais,f1.bitSig*bitSig);
	 res.perteMontice();

	 // affichage pour le debugage
	 if (degMode) printf("\nEXP :fs1[%f]*fs2[%f]=%f",this->getFolat(),f1.getFolat(),res.getFolat());
     if (degMode==2) if  ((res.getFolat() -(this->fSource*f1.fSource))>0.0001) getchar();
	 return (res);
  }
  else {
	 VirtalFloat res((result/2),1+exp+f1.exp-bais,f1.bitSig*bitSig);
	 res.perteMontice();

	 // affichage pour le debugage
	 if (degMode) printf("\nEXP :fs1[%f]*fs2[%f]=%f",this->getFolat(),f1.getFolat(),res.getFolat());
     if (degMode==2) if  ((res.getFolat() -(this->fSource*f1.fSource))>0.0001) getchar();
	 return (res);
  }
}