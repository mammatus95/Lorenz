/*Lorenz Attroktor*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>


#define N 10000
#define DeltaT 0.01
#define DeltaT2 0.005
#define R 28.0   /*Rayleigh Zahl*/
#define SIG 10.0 /*Prandtl - Zahl*/
#define B 8/3    /*Aspekt - Zahl*/

float max_time (void){
    return N*DeltaT;
}

/*Velocity*/
double x_func( double x, double y){
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

void errofile (FILE *datei) {
    if( (datei=fopen("test.txt","w+")) == NULL) {
        fprintf(stderr, "Kann Datei nicht oeffnen\n");
        exit(-1);
    }
    return;
}

/*Write output in a file*/
void fileoutput (double *X, double* Y, double* Z, FILE *data){

    fprintf(data,"%.10lf;", (*X));
    fprintf(data,"%.10lf;", (*Y));
    fprintf(data,"%.10lf\n", (*Z));
    return;
}

float j=0,k=0;


int main (void){

    int i = 0;
    double X=10,Y=0,Z=0;
    //errofile (datei);

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
