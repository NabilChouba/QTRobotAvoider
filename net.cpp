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
	if (typeFX_VF==0)
	{
		fprintf(fp,"input %d\n",usedNetWork_FX->nbr_net[0]);
		for (int i=1;i<usedNetWork_FX->nbr_layer;i++)
			fprintf(fp,"layer  %d\n",usedNetWork_FX->nbr_net[i]);
		fprintf(fp,"output %d\n",usedNetWork_FX->nbr_net[usedNetWork_FX->nbr_layer]);
	}
	else 
	{
		fprintf(fp,"input %d\n",usedNetWork_VF->nbr_net[0]);
		for (int i=1;i<usedNetWork_VF->nbr_layer;i++)
			fprintf(fp,"layer  %d\n",usedNetWork_VF->nbr_net[i]);
		fprintf(fp,"output %d\n",usedNetWork_VF->nbr_net[usedNetWork_VF->nbr_layer]);	
	}


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
	FILE * fp=NULL;
	qWarning("%s",filename);

	vecteur *v;
	int i_in;
	int i_out;

	if (typeFX_VF==0)
	{
		v=new vecteur(usedNetWork_FX->nbr_net[0],usedNetWork_FX->nbr_net[usedNetWork_FX->nbr_layer]);
		i_in =usedNetWork_FX->nbr_net[0];
		i_out =usedNetWork_FX->nbr_net[usedNetWork_FX->nbr_layer];
	}
	else 
	{
		v=new vecteur(usedNetWork_VF->nbr_net[0],usedNetWork_VF->nbr_net[usedNetWork_VF->nbr_layer]);
		i_in =usedNetWork_VF->nbr_net[0];
		i_out =usedNetWork_VF->nbr_net[usedNetWork_VF->nbr_layer];
	}
	
	char ligne [100];
	char * t=NULL;
	int nbr_patternTemp;
	fp= fopen(filename,"r");
	if (!fp) {
		printf("unable to open learn file\n");
		return 0;
	}
	
	int n=0;
	
	while (fgets(ligne,100,fp))
	{
		if (t=strstr(ligne,"NBR_pat"))
		{
			sscanf(t+7,"%d",&nbr_patternTemp);
	
			if (typeFX_VF==0)  usedNetWork_FX->allocPattern(nbr_patternTemp);
			else usedNetWork_VF->allocPattern(nbr_patternTemp);
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
	if (typeFX_VF==0){
		usedNetWork_FX->freePattern();
		usedNetWork_FX->allocPattern(nbr_pattern);
	}
	else {
		usedNetWork_VF->freePattern();
		usedNetWork_VF->allocPattern(nbr_pattern);	
	}


}
net::setVectorToNetwork()
{
	//pour le resaux de neurone l'input pin et pout 
	//et lite apartire du ficher architecture

	vecteur *v;
	int pin =(vect->first())->nbrIN;
	int pout=(vect->first())->nbrOut;
	int n=0;
	v=vect->first();
	
	while (v)
	{
		
		//IN_vect 
		for (int i=0;i<pin;i++)		
		{
			if (typeFX_VF==0) usedNetWork_FX->i_p(n,i)=v->in[i];
			else usedNetWork_VF->i_p(n,i)=v->in[i];
		}
	
		//OUT_vect
		for (int j=0;j<pout;j++)
		{
			if (typeFX_VF==0) usedNetWork_FX->o_p(n,j)= v->out[j];
			else usedNetWork_VF->o_p(n,j)= v->out[j];
		}
		
		n++;	
		v = vect->next();
	}
		
}