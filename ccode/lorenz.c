//**************************************************************************************************
//    Lorenz Attroctor
//    lorenz.c                                                                
//    COPYRIGHT (c) 2024 by Mammatuscloud
//    All rights reserved
//**************************************************************************************************

#include "lorenz.h"


void errofile (FILE *datei) {
    if( (datei=fopen("test.txt","w+")) == NULL) {
        fprintf(stderr, "Kann Datei nicht oeffnen\n");
        exit(-1);
    }
    return;
}  

int main (void){

    int i = 0;
    double X=10, Y=0, Z=0;
    //errofile (datei);

    X = 10.0;
    Y = 0;
    Z = 0;

    while (i<=N){
        runge_kutta( &X, &Y, &Z);
        i++;
    }
    printf("%.10lf\n" , X);
    return 0;
}
