//**************************************************************************************************
//    Lorenz Attroctor
//    lorenzlib.c                                                                
//    COPYRIGHT (c) 2024 by Mammatuscloud
//    All rights reserved
//**************************************************************************************************

#include "lorenzlib.h"


float getMaxTime(void) {
    return (float)N * DeltaT;
}

/*Velocity*/
double x_func(double x, double y){
    /*
    This function estimate the time derivation of the Velocity (so it is acceleration).
    */
    return (-SIG*x + SIG*y);
}

/*Temperature*/
double y_func(double x, double y, double z){
    /*
    This function estimate the time derivation of the Temprature.
    */
    return (-y + R*x - x*z);
}

/*Instability (Temperaturschichtung)*/
double z_func(double x,double y,double z){
    /*
    This function estimate the time derivation of the Instability.
    */
    return (-B*z + x*y);
}

/*conserved quantities*/
double h_func(double y,double z){
    return 0.5*y*y + 0.5*z*z - R*z;
}

double c_func(double x, double z){
    return 0.5*x*x - SIG*z;
}

void runge_kutta(double* X, double* Y, double* Z){
    /*
    Parameters :
    ------------
    X : Velocity as double pointer
    Y : Temperature as double pointer
    Z : Instability as double pointer
    Returns:
    --------
    nothing
    */

    double k1_x=0, k1_y=0, k1_z=0, k2_x=0, k2_y=0, k2_z=0, k3_x=0, k3_y=0, k3_z=0, k4_x=0, k4_y=0, k4_z=0;

    k1_x = x_func( (*X), (*Y) );
    k1_y = y_func( (*X), (*Y), (*Z));
    k1_z = z_func( (*X), (*Y), (*Z));

    k2_x = x_func( (*X)+(DeltaT2*k1_x), (*Y)+(DeltaT2*k1_y) );
    k2_y = y_func( (*X)+(DeltaT2*k1_x), (*Y)+(DeltaT2*k1_y), (*Z)+(DeltaT2*k1_z));
    k2_z = z_func( (*X)+(DeltaT2*k1_x), (*Y)+(DeltaT2*k1_y), (*Z)+(DeltaT2*k1_z));

    k3_x = x_func( (*X)+(DeltaT2*k2_x), (*Y)+(DeltaT2*k2_y));
    k3_y = y_func( (*X)+(DeltaT2*k2_x), (*Y)+(DeltaT2*k2_y), (*Z)+(DeltaT2*k2_z));
    k3_z = z_func( (*X)+(DeltaT2*k2_x), (*Y)+(DeltaT2*k2_y), (*Z)+(DeltaT2*k2_z));

    k4_x = x_func( (*X)+(DeltaT*k3_x), (*Y)+(DeltaT*k3_y));
    k4_y = y_func( (*X)+(DeltaT*k3_x), (*Y)+(DeltaT*k3_y), (*Z)+(DeltaT*k3_z));
    k4_z = z_func( (*X)+(DeltaT*k3_x), (*Y)+(DeltaT*k3_y), (*Z)+(DeltaT*k3_z));

    (*X) = (*X) + (DeltaT/6.0) * (k1_x +2*k2_x + 2*k3_x + k4_x);
    (*Y) = (*Y) + (DeltaT/6.0) * (k1_y +2*k2_y + 2*k3_y + k4_y);
    (*Z) = (*Z) + (DeltaT/6.0) * (k1_z +2*k2_z + 2*k3_z + k4_z);

    return;
}


/*Write output in a file*/
void fileoutput (double *X, double* Y, double* Z, FILE *data){
    fprintf(data,"%.10lf;", (*X));
    fprintf(data,"%.10lf;", (*Y));
    fprintf(data,"%.10lf\n", (*Z));
    return;
}
