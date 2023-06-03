import java.util.Scanner;

public class H_SqrtSquare {
    static final double EPS3 = 0.000001;
    static final double EPS1 = 1;
    static final double EPS2 = 0.001;

    static double expr(double x) {
        return x * x + Math.sqrt(x);
    }

    static double search(double C, double eps, double left, double right) {
        double l = left;
        double r = right;
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
        double c = scanner.nextDouble();
        double x = search(c, EPS1, 1.0, Math.sqrt(c));
        x = search(c, EPS2, x - EPS1, x + EPS1);
        x = search(c, EPS3, x - EPS2, x + EPS2);
        System.out.print(x);
    }
}