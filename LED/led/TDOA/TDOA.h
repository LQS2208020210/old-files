#ifndef __TDOA_H
#define	__TDOA_H
#include "main.h"
#include <math.h>

typedef struct
{
	double x;
	double y;
	double r21;
	double r31;
	double r41;
	double a1;
	double a2;
	double L;
}_TDOA;


extern _TDOA TDOA_S;
void TDOA_Init(_TDOA *TDOA_S);
void TDOA_Get_distanceANDangle(_TDOA *TDOA_S);

#endif
