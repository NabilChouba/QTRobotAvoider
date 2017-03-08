#include "sigmoid.h"

 float sigmoidExp (float x,float borneSigmoid,float pasSigmoid) {
	
	//nos borne
	if (x < -borneSigmoid) return(0.0);
	if (x >  borneSigmoid) return(1.0);

    float xExp=((int)(x/pasSigmoid))*pasSigmoid;
  	return (   1.0 / ( 1.0 + exp( -1 * xExp )));
}

