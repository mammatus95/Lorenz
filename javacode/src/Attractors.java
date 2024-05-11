public abstract class Attractors {
    /* calc coordinates */
    public abstract double calc_x(double input_x, double input_y, double input_z);
    public abstract double calc_y(double input_x, double input_y, double input_z);
    public abstract double calc_z(double input_x, double input_y, double input_z);

    public void wrapper_run(double x_start, double y_start, double z_start, int n){
        double x_value = x_start;
        double y_value = y_start;
        double z_value = z_start;
        System.out.printf("Start value is %f\n", x_value);
        for (int i = 1; i < n; i++) {
            x_value = calc_x(x_value, y_start, z_start);
            y_value = calc_y(x_value, y_start, z_start);
            z_value = calc_z(x_value, y_start, z_start);
            //if (i % 10 == 0) {
            System.out.printf("Value at %d is %1.2f\n", i, x_value);
            //}
        }
    }

    public void euler_run(double x_start, double y_start, double z_start, double time, double dt){
        double x_value = x_start;
        double y_value = y_start;
        double z_value = z_start;
        double x_change = 0, y_change  = 0, z_change  = 0;
        int n = (int) (time/dt);
        System.out.println("Time: " + time);
        System.out.println("Step: " + dt);
        System.out.println("Count: " + n);
        System.out.printf("Start value is (%1.2f,%1.2f,%1.2f)\n", x_start, y_start, z_start);
        for (int i = 1; i < n; i++) {
            x_change = calc_x(x_value, y_value, z_value)*dt;
            y_change = calc_y(x_value, y_value, z_value)*dt;
            z_change = calc_z(x_value, y_value, z_value)*dt;
            x_value += x_change;
            y_value += y_change;
            z_value += z_change;
            if (i % (int) (1/dt) == 0) {
                System.out.printf("Change (%1.2f,%1.2f,%1.2f)\n", x_change, y_change, z_change);
                System.out.printf("Value at %1.2f is (%1.2f,%1.2f,%1.2f)\n", i*dt, x_value, y_value, z_value);
            }
        }
    }
}
