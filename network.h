//****** neural test float version 1 working good
/***       next modification supporting fpu mul and add 
*/
   
#ifndef network_included
#define network_included

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <qapplication.h> 
#include <qlcdnumber.h>

#define LERN_FILE "default.txt"
//type d'arrithmetique
#include "FixedPoint.h"
#include "VirtalFloat.h"
#include "sigmoid.h"

class networkFather
{

 public :
	int StopLearn;
	QLCDNumber *LCDErr,*LCDstep;

	float ETA ;

	int nbr_net[10];
	int nbr_pattern ;
	int setp;



	bool deb ,workSigmoidApprox; //=false;
	int nbr_pat ; //=0;

	int nbr_layer ; //=0;


	float pasSigmoid,borneSigmoid;
	virtual float launchLearn()=0;
	
	virtual void allocPattern(int nbr_Pattern)=0;
	virtual void load_learn_data(char * filename)=0;	
	virtual void freePattern(){};
	virtual float getResulta(float * num_pat)=0;
	virtual void setOutput(int t,int i,float val)=0;
	virtual void setInput(int t,int i,float val)=0;
	virtual void free_network(){};
	virtual void save_w(char *filename)=0;
	virtual void Load_w(char *filename)=0;
	
	
	virtual void update_w()=0;
	virtual void back_propagate()=0;
	virtual void calculate_err( int layer,int net)=0;
	virtual void propagate()=0;
	virtual void activate_fonc(int layer,int net)=0;
	virtual float sigmoidDeriv(float x)=0;
	virtual float sigmoid (float x)=0;
	virtual void get_info(int layer,int net)=0;
	virtual void show_w()=0;
	virtual void init_w()=0;
	
	virtual void malloc_network()=0;
	virtual void load_network( char * filename)=0;


	virtual void setSigmoidApprox(float laborneSigmoid,float lepasSigmoid,bool laworkSigmoidApprox)=0;
	


	//networkFather(){};

   virtual ~networkFather(){
		
		qWarning("je mord pere ");
	};

};


template<class floatN>
class network : public networkFather  
{

  public:

	float minW,maxW;
	void save_w(char *filename);
	void Load_w(char *filename);

	floatN* w_matrix[10];
	floatN* x_vector[10];
	floatN* bias_vector[10];

	floatN* s_vector[10];
	floatN* err_vector[10] ;
	floatN ** input_pattern;
	floatN ** output_pattern;
	
	floatN *max_err_tol ; //=   0.1;

	floatN *d_vector ;
	floatN *total_err ; //=0;

	float launchLearn();
	void getMinMax();
	void allocPattern(int nbr_Pattern);
	floatN test(int num_pat);
	floatN learn(int num_pat);
	floatN get_err();
	void load_learn_data(char * filename);
	void update_w();
	void back_propagate();
	void calculate_err( int layer,int net);
	void propagate();
	void activate_fonc(int layer,int net);
	float sigmoidDeriv(float x);
	float sigmoid (float x);
	void get_info(int layer,int net);
	void show_w();
	void init_w();
	void free_network();
	void malloc_network();
	void load_network( char * filename);
	floatN & err(int layer,int i);
	floatN & s(int layer,int i);
	floatN & b(int layer,int i);
	floatN & x(int layer,int i);
	floatN & o_p(int t,int i);
	floatN & i_p(int t,int i);
	void setOutput(int t,int i,float val){o_p(t,i)=val;};
	void setInput(int t,int i,float val){i_p(t,i)= val;};

	void setSigmoidApprox(float laborneSigmoid,float lepasSigmoid,bool laworkSigmoidApprox)
	{borneSigmoid=laborneSigmoid;pasSigmoid=lepasSigmoid;workSigmoidApprox=laworkSigmoidApprox;};


	floatN & w(int layer,int i,int j);
	network();
	~network(){		
		qWarning("je mord fise");
		free_network();
		freePattern();
	};
	void freePattern();
	float getResulta(float * num_pat);

};


template<class floatN>
network<floatN>::network()
{
	StopLearn=0;
	minW=9999;
	maxW=-9999;

	setp =0;

	borneSigmoid=pasSigmoid=0.0f;

	nbr_pattern = 0;
	ETA=  0.1f;
	workSigmoidApprox=false;
	max_err_tol=new floatN(0.1f);

	deb = 0;//false ;
	nbr_pat =0;
	nbr_layer =0;
	total_err=new floatN( 0.0f);

	//Load network architector
	load_network(LERN_FILE);//avoire
	
	//Allocation de memoire needed
	malloc_network();

	//inialisatioin des w
	init_w();

	//set load patern
//	load_learn_data( LERN_FILE);
}


template<class floatN>
float network<floatN>::launchLearn()
{

	
	
	floatN err_temp=0;
	
	
	//while ( ){	
	
		floatN max_error=0;
		err_temp=max_error;
		for (int numpat=0;numpat<nbr_pattern;numpat++){

			floatN error=learn(numpat);
			if (error>max_error ) max_error =error;
		
		}

		char txt[10];
		float floatErr=(float)(max_error);

		sprintf(txt,"%0.5f",floatErr);
		
		qWarning("max error=%f,setp%d\r",(float)(max_error),setp);
		
		
		LCDErr->display( txt );
		LCDstep->display( setp );
		setp++;

		return ((float)(max_error));
	//	if (max_error <(*max_err_tol)) break;
	//}
	//getMinMax();
	
}

template<class floatN>
floatN & network<floatN>::w(int layer,int i,int j){// w_layer, rg_net  ,rg_net_upper_layer
	return *(w_matrix[layer]+j+i*nbr_net[layer+1]);
}

template<class floatN>
floatN & network< floatN>::i_p(int t,int i){
	return *( *(input_pattern+t) +i);
}

template<class floatN>
floatN & network<floatN>::o_p(int t,int i){
	return * (* (output_pattern+t) +i);
}

template<class floatN>
floatN & network<floatN>::x(int layer,int i){// net_layer,rg_net 
	return *(x_vector[layer]+i);
}

template<class floatN>
floatN & network< floatN>::b(int layer,int i){// net_layer,rg_net 
	return *(bias_vector[layer]+i);
}

template<class floatN>
floatN & network< floatN>::s(int layer,int i){// net_layer,rg_net 
	return *(s_vector[layer]+i);
}

template<class floatN>
floatN & network< floatN>::err(int layer,int i){// net_layer,rg_net 
	return *(err_vector[layer]+i);
}

template<class floatN>
void network< floatN>::load_network( char * filename){
	FILE * fp=NULL;
	char ligne [80];
	char * t=NULL;
	fp= fopen(filename,"r");
	if (!fp) {
		printf("unable to open network file\n");
		return;
	}
	
	int conteur=0;
	while (fgets(ligne,80,fp))
	{
		if (t= strstr(ligne,"input")) {
			sscanf(t+5,"%d",&nbr_net[0]);
			
		}else 
		if (t= strstr(ligne,"layer")) {
			nbr_layer++;
			sscanf(t+5,"%d",&nbr_net[nbr_layer]);

		}
		else 
		if (t= strstr(ligne,"output")) {
			nbr_layer++;
			sscanf(t+6,"%d",&nbr_net[nbr_layer]);
		}
	}
	fclose(fp);

}

template<class floatN>
void network< floatN>::malloc_network(){
	for (int  i=0;i<=nbr_layer;i++)
	{
		if (i<nbr_layer) w_matrix[i]= (floatN*) (malloc (sizeof(floatN)*nbr_net[i]*nbr_net[i+1]));
		x_vector[i]= (floatN*) malloc (sizeof(floatN)*nbr_net[i]);
		bias_vector[i]= (floatN*) malloc (sizeof(floatN)*nbr_net[i]);
		d_vector=(floatN*) malloc (sizeof(floatN)*10);
		s_vector[i]= (floatN*) malloc (sizeof(floatN)*nbr_net[i]);
		err_vector[i]= (floatN*) malloc (sizeof(floatN)*nbr_net[i]);
	}
}

template<class floatN>
void network< floatN>::free_network(){
	/*
	for (int  i=0;i<=nbr_layer;i++)
	{
		if (i<nbr_layer) free(w_matrix[i]);
		free(x_vector[i]);
		free(bias_vector[i]);
		
		free(s_vector[i]);
		free(err_vector[i]);

	}
	free(d_vector);
	*/
}

template<class floatN>
void network< floatN>::init_w(){

	srand(38);//il doit etre un parametre dynamique
	for (int layer=0;layer<nbr_layer;layer++)
		for (int i=0;i<nbr_net[layer];i++)
			
			for (int j=0;j<nbr_net[layer+1];j++){
				if (i==0 )b(layer+1,j)=(floatN)((rand() % 32727) / 32737.0);
				w(layer,i,j)=(floatN)((rand() % 32727) / 32737.0);
		}
				
			
}

template<class floatN>
void network< floatN>::show_w(){
for (int layer=0;layer<nbr_layer;layer++)
		for (int i=0;i<nbr_net[layer];i++)
		{
			for (int j=0;j<nbr_net[layer+1];j++){
				printf("layer %d w(i%d,j%d)=%f  \n",layer,i,j,(float) (w(layer,i,j)));
				//w(layer,i,j).showProp();
//elle marche si floatN != float error
				//w(layer,i,j).showPropBin();
			}
			printf("\n");
		}

}

template<class floatN>
void network< floatN>::getMinMax(){
for (int layer=0;layer<nbr_layer;layer++)
		for (int i=0;i<nbr_net[layer];i++)
			for (int j=0;j<nbr_net[layer+1];j++)
			{
				if (minW >(float) (w(layer,i,j))) minW = (float) (w(layer,i,j));
				if (maxW <(float) (w(layer,i,j))) maxW = (float) (w(layer,i,j));
			}
	//QMessageBox::information( this, "Application name", );
			qWarning("the Max =%f   ,  the Min%f",maxW ,minW);

}



template<class floatN>
void network< floatN>::get_info(int layer,int net){
	printf("x(layer%d,net%d)=%f\n",layer,net,(float)(x(layer,net)));
}


template<class floatN>
float network< floatN>::sigmoid (float x) {
  if (workSigmoidApprox) 
	  //valeur avec aproximation
	  return (sigmoidExp(x,borneSigmoid,pasSigmoid));//c mon erreur a voire

  //valeur real du sigmo
  return (   1.0f / ( 1.0f + exp( -1.0f * x )));
}

template<class floatN>
float network< floatN>::sigmoidDeriv(float x){
	
	  return ((sigmoid(x) * (1.0 - sigmoid(x))));
}


template<class floatN>
void network< floatN>::activate_fonc(int layer,int net){
	if (layer==0) return ;
	 floatN I=b(layer,net);

	 if (deb) printf("\t %f * %f  + %f \n",
			1.0,(float)(b(layer,net)),(float) (I));
	 for ( int i=0;i<nbr_net[layer-1];i++){
		I=I+w(layer-1,i,net)*x(layer-1,i);
		if (deb) printf("\t %f * %f  + %f \n",
			(float)(x(layer-1,i)),(float)(w(layer-1,i,net)),(float)(I));
	 }
	    if (deb) printf(" Som =%f ",(float)(I));
		s(layer,net)=I;
		x(layer,net)=floatN (sigmoid((float)(I)));

		if (deb) {printf("sig =%f  \n",
			sigmoid((float)(I)) );}
	
}

template<class floatN>
void network< floatN>::propagate(){
	
	for ( int layer=1;layer<=nbr_layer;layer++)
		for ( int net=0;net<nbr_net[layer];net++)
			activate_fonc(layer,net);
	
}

template<class floatN>
void network< floatN>::calculate_err( int layer,int net){
	floatN res=0;
	
		
	if (layer==nbr_layer) {

		//err(layer,net)=(d_vector[net]-x(layer,net))*sigmoidDeriv(s(layer,net));
		
		err(layer,net)=(d_vector[net]-x(layer,net));//*(1-x(layer,net))*x(layer,net);
			
	}
	else {
		for ( int i=0;i<nbr_net[layer+1];i++){
			res=res+err(layer+1,i)*w(layer,net,i);
		}
			//err(layer,net)=res*sigmoidDeriv(s(layer,net));
		
			err(layer,net)=res*(floatN(1.0)-x(layer,net))*x(layer,net);
	}
}

template<class floatN>
void network< floatN>::back_propagate(){
	for ( int layer=nbr_layer;layer>0;layer--)
		for ( int i=0;i<nbr_net[layer];i++)
			calculate_err(layer,i);
}

template<class floatN>
void network<floatN>::update_w(){
	for ( int layer=0;layer<nbr_layer;layer++)
	{
	/*	floatN length =0;
		for ( int l=0;l<nbr_net[layer];l++)
			length += x(layer,l)*x(layer,l);
		if (length<0.1) length=0.1;*/

		for ( int i=0;i<nbr_net[layer];i++)
		
			for ( int j=0;j<nbr_net[layer+1];j++)
			{
				w(layer,i,j)=w(layer,i,j)+err(layer+1,j)*floatN(ETA)*x(layer,i);///length;
				b(layer+1,j)=b(layer+1,j)+floatN(ETA)*err(layer+1,j);///length;
			
			}
	}	
}

template<class floatN>
void network<floatN>::load_learn_data(char * filename){
	FILE * fp=NULL;
	char ligne [100];
	char * t=NULL;
	fp= fopen(filename,"r");
	if (!fp) {
		printf("unable to open learn file\n");
		return;
	}
	int n_i=0;
	int n_o=0;

	while (fgets(ligne,100,fp))
	{
		if (t=strstr(ligne,"NBR_pat")){
			sscanf(t+7,"%d",&nbr_pattern);
			input_pattern=(floatN **) malloc(nbr_pattern*sizeof(floatN *));
			output_pattern=(floatN **) malloc(nbr_pattern*sizeof(floatN *));
			for (int t=0;t<nbr_pattern;t++){
				*(input_pattern+t) =(floatN *) malloc( nbr_net[0]*sizeof(floatN));
				*(output_pattern+t) =(floatN *) malloc( nbr_net[nbr_layer]*sizeof(floatN));
			}

		}
		
		if ((t= strstr(ligne,"IN_vect")) && n_i<nbr_pattern) {
			int i=0;
			t+=8;
			float temp;
			while (1){
				sscanf(t,"%f",&temp);i_p(n_i,i)=floatN(temp);
				while (*t!=' '&& *t!='\0') t++;
				if (*t=='\0') break;
				t++;
				i++;

			}
				n_i++;
		}else 
		if ((t= strstr(ligne,"OUT_vect")) &&n_o<nbr_pattern) {
			int i=0;
			t+=9;
		    float temp;
			while (1){
				sscanf(t,"%f",&temp);
				o_p(n_o,i)=floatN(temp);
		
				while (*t!=' '&& *t!='\0') t++;
				if (*t=='\0') break;
				t++;
				i++;
			}
			n_o++;
		}

		
	}
	fclose(fp);
}

template<class floatN>
floatN network<floatN>::get_err(){
	floatN absError =0.0;
	for (int i=0;i<nbr_net[nbr_layer];i++)
	{
		floatN delta=d_vector[i] - x(nbr_layer,i);
		if ((float) (delta)>0) absError = absError+delta;
		else absError = absError-delta;
	//	absError = absError+ delta.getFolat()>0? delta:-delta;
	}
	return absError ;
}

template<class floatN>
floatN network<floatN>::learn(int num_pat){
	int net;
	for (net=0;net<nbr_net[0];net++)
		x(0,net)=i_p(num_pat,net);
	for (net=0;net<nbr_net[nbr_layer];net++)
		d_vector[net]=o_p(num_pat,net);
	
	propagate();
	back_propagate();
	update_w();
	return (get_err());
	
	
}

template<class floatN>
floatN network<floatN>::test(int num_pat){
	int net;
	for (net=0;net<nbr_net[0];net++)
		x(0,net)=i_p(num_pat,net);

	for (net=0;net<nbr_net[nbr_layer];net++)
		d_vector[net]=o_p(num_pat,net);
	propagate();

	return (get_err());
}	

/******************************************************************************/

template<class floatN>
float network<floatN>::getResulta(float * inputTest){
	int net;
	for (net=0;net<nbr_net[0];net++)
		x(0,net)=inputTest[net];

	propagate();

	return ((float)(x(nbr_layer,0)));
	

}	
/*
network::launchLearn()
{

	int setp=0;
	float err_temp=0;
	while (1 && StopLearn==0){	
		float max_error=0;
		err_temp=max_error;
		for (int numpat=0;numpat<nbr_pattern;numpat++){

			float error=learn(numpat);
			if (error>max_error ) max_error =error;
		
		}

		qWarning("max error=%f,setp%d\r",max_error ,setp);
		char txt[10];
		sprintf(txt,"%0.5f",max_error);
		LCDErr->display( txt );
		LCDstep->display( setp );
		setp++;

		if (max_error <max_err_tol) break;
	}
}
*/



template<class floatN>
void network<floatN>::save_w(char *filename){

	FILE * fp= fopen(filename,"w");
	
	for (int layer=0;layer<nbr_layer;layer++){
		for (int i=0;i<nbr_net[layer];i++)
		{
			
		   for (int j=0;j<nbr_net[layer+1];j++)
				fprintf(fp,"%f\n",(float)(w(layer,i,j)));
		}

		for (int j=0;j<nbr_net[layer+1];j++)
			fprintf(fp,"%f",(float) (b(layer+1,j)));
		
	}
	fclose(fp);
						
}

template<class floatN>
void network<floatN>::Load_w(char *filename){
	FILE * fp=NULL;
	fp= fopen(filename,"r");
	float f;
	for (int layer=0;layer<nbr_layer;layer++)
	{
		for (int i=0;i<nbr_net[layer];i++)
		{
			for (int j=0;j<nbr_net[layer+1];j++)
			{
				fscanf(fp,"%f\n",&f);
				w(layer,i,j)=floatN(f);
			}
		}
		for (int m=0;m<nbr_net[layer+1];m++)
		{
			fscanf(fp,"%f",&f);
			b(layer+1,m)=floatN(f);
		}			
	}
}

template<class floatN>
void network<floatN>::allocPattern(int nbr_Pattern)
{	
	nbr_pattern=nbr_Pattern;
	input_pattern=(floatN **) malloc(nbr_pattern*sizeof(floatN *));
	output_pattern=(floatN **) malloc(nbr_pattern*sizeof(floatN *));
			
	for (int t=0 ;t<nbr_pattern ;t++){
	  *(input_pattern+t)  = (floatN *) malloc( nbr_net[0]*sizeof(floatN));
	  *(output_pattern+t) = (floatN *) malloc( nbr_net[nbr_layer]*sizeof(floatN));
	}
}

//free l espase de memoire alouer pour la gestion des patern

template<class floatN>
void network<floatN>::freePattern()
{
/*
	for (int t=0 ;t<nbr_pattern ;t++){
			  free(*(input_pattern +t)) ;
			  free(*(output_pattern+t)) ;
	}
	free(input_pattern ) ;
	free(output_pattern) ;
	
*/
}

#endif