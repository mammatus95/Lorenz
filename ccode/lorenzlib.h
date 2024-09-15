//**************************************************************************************************
//    Lorenz Attroctor
//    lorenzlib.h                                                                
//    COPYRIGHT (c) 2024 by Mammatuscloud
//    All rights reserved
//**************************************************************************************************

#ifndef LORENZLIB_H
#define LORENZLIB_H 1

#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// prototypes
float   getMaxTime(void);
double  x_func(double x, double y);
double  y_func(double x, double y, double z);
double  z_func(double x,double y,double z);
double  h_func(double y,double z);
double  c_func(double x, double z);
void    runge_kutta(double* X, double* Y, double* Z);
void    fileoutput (double *X, double* Y, double* Z, FILE *data);

#endif
