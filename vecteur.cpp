#include "vecteur.h"

vecteur::vecteur(int In,int Out):nbrIN(In),nbrOut(Out){
		in =(float *) malloc( In*sizeof(float));
		out=(float *) malloc( Out*sizeof(float));
	}

net::net(){
		vect= new QList<vecteur>();
		nbr_pattern = 0;
		load =false;
	};
vecteur::vecteur(vecteur *v)
{
		nbrIN=v->nbrIN ;
		nbrOut=v->nbrOut;

		in =(float *) malloc( nbrIN *sizeof(float));
		out=(float *) malloc( nbrOut *sizeof(float));

		for (int i=0;i<nbrIN;i++)
			in[i]=v->in[i];

		for (int ip=0;ip<nbrOut;ip++)
			out[ip]=v->out[ip];
	
}

net::addvect(vecteur *v){
	nbr_pattern++;
	vect->append (new vecteur(v));

}

net::saveVector(char *fileName){
	FILE * fp=NULL;

	char * t=NULL;
	vecteur *v;
	
	fp= fopen(fileName,"w+");
	if (!fp) {
		printf("unable to open learn file\n");
		return 0;
	}


	//architecture du resaeux
	fprintf(fp,"input %d\n",usedNetWork->nbr_net[0]);
	for (int i=1;i<usedNetWork->nbr_layer;i++)
		fprintf(fp,"layer  %d\n",usedNetWork->nbr_net[i]);
	fprintf(fp,"output %d\n",usedNetWork->nbr_net[usedNetWork->nbr_layer]);


	int pin =(vect->first())->nbrIN;
	int pout=(vect->first())->nbrOut;
	int countVect=0;
	
	// NBR_pat 20
	v=vect->first();
	while (v)
	{
		countVect++;
		v = vect->next();
	}
	
	fprintf(fp,"\nNBR_pat %d  \n",countVect);


	// IN_vect 
	// OUT_vect 
	v=vect->first();
	while (v)
	{
		//ecriture du vecteur in
		fprintf(fp,"\nIN_vect ");
		for (int i=0;i<pin;i++)
		{
			fprintf(fp,"%f ",v->in[i]);
		}

		//ecriture du vecteur out
		fprintf(fp,"\nOUT_vect ");
		for (int ip=0;ip<pout;ip++)
		{
			fprintf(fp,"%f ",v->out[ip]);
		}

		v = vect->next();
	}
	fclose(fp);
return 0;
}

net::loadVector(char * filename){

	//delete all vector before loading the file
	delete(vect);
	vect= new QList<vecteur>();
	nbr_pattern = 0;

	FILE * fp=NULL;
	qWarning("%s",filename);
	vecteur *v=new vecteur(usedNetWork->nbr_net[0],usedNetWork->nbr_net[usedNetWork->nbr_layer]);
	int i_in =usedNetWork->nbr_net[0];
	int i_out =usedNetWork->nbr_net[usedNetWork->nbr_layer];
	char ligne [1024];
	char * t=NULL;
	int nbr_patternTemp;
	fp= fopen(filename,"r");
	if (!fp) {
		printf("unable to open learn file\n");
		return 0;
	}
	
	int n=0;
	
	while (fgets(ligne,1024,fp))
	{
		if (t=strstr(ligne,"NBR_pat"))
		{
			sscanf(t+7,"%d",&nbr_patternTemp);
			usedNetWork->allocPattern(nbr_patternTemp);
		}

	
		
		if ((t= strstr(ligne,"IN_vect")) && n <nbr_patternTemp) 
		{
			int i=0;
			t+=8;
			
			while (1)
			{
			//	sscanf(t,"%f",&usedNetWork->i_p(n_i,i));
			//	v.in[i]=usedNetWork->i_p(n_i,i);
				
				sscanf(t,"%f",&v->in[i]);
				while (*t!=' '&& *t!='\0') t++;
				if (*t=='\0') break;
				t++;
				i++;

			}
				//n_i++;
				v->nbrIN=i_in;
		}
		else 
		if ((t= strstr(ligne,"OUT_vect")) && n <nbr_patternTemp ) {
			int i=0;
			t+=9;
		
			while (1)
			{
			//	sscanf(t,"%f",&usedNetWork->o_p(n_o,i));
			//	v.out[i]=usedNetWork->o_p(n_o,i);

				sscanf(t,"%f",&v->out[i]);
				while (*t!=' '&& *t!='\0') t++;
				if (*t=='\0') break;
				t++;
				i++;
			}
			//n_o++;
			n++;
			v->nbrOut=i_out;
			addvect(v);
		}

		
	}

	fclose(fp);
	return 0;
}
net::restNetwork()
{
	usedNetWork->freePattern();
	usedNetWork->allocPattern(nbr_pattern);


}
net::setVectorToNetwork()
{
	//pour le resaux de neurone l'input pin et pout 
	//et lite apartire du ficher architecture

   vecteur *v;
   if (vect->first()){
	int pin =(vect->first())->nbrIN;
	int pout=(vect->first())->nbrOut;
	int n=0;
	v=vect->first();
	
	while (v)
	{
		
		//IN_vect 
		for (int i=0;i<pin;i++)		
			usedNetWork->setInput(n,i,v->in[i]);
	
		//OUT_vect
		for (int j=0;j<pout;j++)
			usedNetWork->setOutput(n,j, v->out[j]);
		
		n++;	
		v = vect->next();
	}
   }
		
}