MODULE mo_lorenz
  IMPLICIT NONE
  PRIVATE

  PUBLIC :: calc_step, print_lorenz, max_time
  
  
  
CONTAINS

  ! Beispiel zur Formatierung
  SUBROUTINE print_lorenz

    IMPLICIT NONE
    real, INTENT(in) :: X,Y,Z  !

    ! Nutzung der automatischen Formatierung
    WRITE(*,*)                X, Y, Z
    ! jetzt verschiedene Varianten der Formatierung mit Formatbeschreiber
    WRITE(*,'(3(F8.2,1X))')   X, Y, Z
  END SUBROUTINE print_lorenz

  SUBROUTINE calc_step
    double precision, intent(in,out) :: X,Y,Z  !
    double precision, intent(in,out) :: H,C
    real, intent(in) :: SIG, R, B !
    real, intent(in) :: DeltaT
    real :: DeltaT2 = DeltaT*0.5
    real :: k1_x=0, k1_y=0, k1_z=0, k2_x=0, k2_y=0, k2_z=0, k3_x=0, k3_y=0, k3_z=0, k4_x=0, k4_y=0, k4_z=0

    k1_x = x_func( X, Y, SIG);
    k1_y = y_func( X, Y, Z, R);
    k1_z = z_func( X, Y, Z, B);

    k2_x = x_func( (X)+(DeltaT2*k1_x), (Y)+(DeltaT2*k1_y), SIG );
    k2_y = y_func( (X)+(DeltaT2*k1_x), (Y)+(DeltaT2*k1_y), (Z)+(DeltaT2*k1_z), R);
    k2_z = z_func( (X)+(DeltaT2*k1_x), (Y)+(DeltaT2*k1_y), (Z)+(DeltaT2*k1_z), B);

    k3_x = x_func( (X)+(DeltaT2*k2_x), (Y)+(DeltaT2*k2_y), SIG );
    k3_y = y_func( (X)+(DeltaT2*k2_x), (Y)+(DeltaT2*k2_y), (Z)+(DeltaT2*k2_z), R);
    k3_z = z_func( (X)+(DeltaT2*k2_x), (Y)+(DeltaT2*k2_y), (Z)+(DeltaT2*k2_z), B);

    k4_x = x_func( (X)+(DeltaT*k3_x), (Y)+(DeltaT*k3_y), SIG );
    k4_y = y_func( (X)+(DeltaT*k3_x), (Y)+(DeltaT*k3_y), (Z)+(DeltaT*k3_z), R);
    k4_z = z_func( (X)+(DeltaT*k3_x), (Y)+(DeltaT*k3_y), (Z)+(DeltaT*k3_z), B);

    (X) = (X) + (DeltaT/6.0) * (k1_x +2*k2_x + 2*k3_x + k4_x);
    (Y) = (Y) + (DeltaT/6.0) * (k1_y +2*k2_y + 2*k3_y + k4_y);
    (Z) = (Z) + (DeltaT/6.0) * (k1_z +2*k2_z + 2*k3_z + k4_z);
    
    H = h_func(Y,Z,R)
    
    C = c_func(X, Z, SIG)
    
    
  END SUBROUTINE calc_step
  
real function max_time (real N, real DeltaT) result(rsl)
    rsl =  N*DeltaT
end function max_time

! Velocity
double precision function x_func( double precision x, double precision y, double precision SIG) result(rsl)
    ! This function estimate the time derivation of the Velocity (so it is acceleration).
    rsl = (-SIG*x + SIG*y)
end function x_func

! Temperature
double precision function y_func(double precision x, double precision y, double precision z, double precision R) result(rsl)
    ! This function estimate the time derivation of the Temprature.
    rsl = (-y + R*x - x*z)
end function y_func

! Instability (Temperaturschichtung)
double precision z_func(double precision x,double precision y,double precision z, double precision B) result(rsl)
    ! This function estimate the time derivation of the Instability.
    rsl = (-B*z + x*y)
end function z_func

! conserved quantities
double precision function h_func(double precision y,double precision z, double precision R) result(rsl)
    rsl = 0.5*y*y + 0.5*z*z - R*z
end function h_func

double precision function c_func(double precision x, double precision z, double precision SIG) result(rsl)
    rsl = 0.5*x*x - SIG*z
end function c_func
  
END MODULE mo_lorenz
