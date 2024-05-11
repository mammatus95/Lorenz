public class Lorenz extends Attractors{
    double sig;
    double r;
    double b;

    public Lorenz(double sig, double r, double b){
        this.sig = sig;
        this.r = r;
        this.b = b;
    }

    @Override
    public double calc_x(double input_x, double input_y, double input_z){
        return this.sig*(-input_x + input_y);
    }

    @Override
    public double calc_y(double input_x, double input_y, double input_z) {
        return input_x*(this.r - input_z) - input_y;
    }

    @Override
    public double calc_z(double input_x, double input_y, double input_z) {
        return -b*input_z + input_x*input_y;
    }
}
