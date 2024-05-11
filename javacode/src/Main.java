public class Main {
    public static void main(String[] args) {

        System.out.println("Hello world!");
        //Logmap logmaptry = new Logmap(1);
        //logmaptry.wrapper_run(1.0, 0, 0, 10);

        Lorenz lorenz_model = new Lorenz(10,28,8.0/3.0);
        lorenz_model.euler_run(1.0, 0, 0, 10, 0.1);
    }
}