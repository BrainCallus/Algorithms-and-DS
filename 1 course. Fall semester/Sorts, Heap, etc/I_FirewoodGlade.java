import java.util.Scanner;

public class I_FirewoodGlade {
    static final double EPS3 = 0.00001;

    static double Vp, Vf, a;

    static double expr(double x) {
        return x / (Vp * Math.sqrt(x * x + (1 - a) * (1 - a)))
                + (x - 1) / (Vf * Math.sqrt(a * a + (1 - x) * (1 - x)));
    }

    static double search(double C, double eps, double left, double right) {
        double l = left;
        double r = right;
        expr(r);
        while (l <= r - eps / 2) {
            double m = l + (r - l) / 2;
            if (expr(m) >= C) {
                r = m;
            } else {
                l = m;
            }
        }
        return r;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Vp = scanner.nextDouble();
        Vf = scanner.nextDouble();
        a = scanner.nextDouble();
        double x = search(0, EPS3, 0.0, 1);
        System.out.print(x);
    }
}