public class Logmap extends Attractors{
    /*Logistic Map*/
    double parameter;

    public Logmap(double parameter){
        this.parameter = parameter;
    }

    @Override
    public double calc_x(double input_x, double input_y, double input_z){
        return this.parameter*input_x*(1-input_x);
    }

    @Override
    public double calc_y(double input_x, double input_y, double input_z) {
        return 0;
    }

    @Override
    public double calc_z(double input_x, double input_y, double input_z) {
        return 0;
    }

}
