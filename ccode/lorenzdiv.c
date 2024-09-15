//**************************************************************************************************
//    Lorenz Attroctor
//    lorenzdiv.c                                                                
//    COPYRIGHT (c) 2024 by Mammatuscloud
//    All rights reserved
//**************************************************************************************************

#include "lorenzdiv.h"

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

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        printf("Hello from thread %d\n", thread_num);
    }

    #pragma omp parallel for schedule (static)  private (j,k)
    for (j=0.1;j<=0.1;j+=0.01){
    for (k=0.1;k<=0.1;k+=0.01){
    //for (double l=-0.1;l<=0.1;l+=0.01){
        X = 10.0 + j;
        Y = 0 + k;
        Z = 0 + k;
        i=0;
        while (i<=N){
            runge_kutta( &X, &Y, &Z);/*
            if (i == 1){
                FILE* datei;
                char name[11] = "l_00001.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 10){
                FILE* datei;
                char name[11] = "l_00010.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 20){
                FILE* datei;
                char name[11] = "l_00020.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 30){
                FILE* datei;
                char name[11] = "l_00030.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 50){
                FILE* datei;
                char name[11] = "l_00050.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 60){
                FILE* datei;
                char name[11] = "l_00060.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 100){
                FILE* datei;
                char name[11] = "l_00100.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 200){
                FILE* datei;
                char name[11] = "l_00200.txt";
                datei = fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 400){
                FILE* datei;
                char name[11] = "l_00400.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 500){
                FILE* datei;
                char name[11] = "l_00500.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 600){
                FILE* datei;
                char name[11] = "l_00600.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 700){
                FILE* datei;
                char name[11] = "l_00700.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 800){
                FILE* datei;
                char name[11] = "l_00800.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 900){
                FILE* datei;
                char name[11] = "l_00900.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 1000){
                FILE* datei;
                char name[11] = "l_01000.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }

            if (i == 5000){
                FILE* datei;
                char name[11] = "l_05000.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }
            if (i == 10000){
                FILE* datei;
                char name[11] = "l_10000.txt";
                datei=fopen(name,"a+");
                fileoutput (&X, &Y, &Z, datei);
                fclose(datei);
            }*/
            i++;
        }
    }}
    return 0;
}
