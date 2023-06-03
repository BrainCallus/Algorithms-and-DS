import java.util.Scanner;

public class C_Inversions {
    static int n;
    static double[] arr;
    static double count;

    static void fill(double[] sourse, double[] target, int start, int finish) {
        if (finish >= 0) System.arraycopy(sourse, start, target, 0, finish);
    }

    static double[] merge(double[] a, double[] b) {
        int i = 0, j = 0;
        double[] c = new double[a.length + b.length];
        while (i < a.length || j < b.length) {
            if (i < a.length && j < b.length) {
                if (b[j] < a[i]) {
                    count= count + a.length-i;
                    c[i + j] = b[j];
                    j++;
                } else {
                    c[i + j] = a[i];
                    i++;
                }
            } else {
                if (j < b.length) {
                    c[i + j] = b[j];
                    j++;
                } else {
                    c[i + j] = a[i];
                    i++;
                }
            }
        }
        return c;
    }

    static double[] mergeSort(double[] mas) {
        int len = mas.length;
        if (len <= 1) return mas;
        double[] l = new double[len / 2];
        double[] r = new double[ len-len / 2];
        fill(mas, l, 0, len / 2);
        fill(mas, r, len / 2,  len-len / 2);
        l = mergeSort(l);
        r = mergeSort(r);
        return merge(l, r);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        arr = new double[n];
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextDouble();
        }
        count = 0.0;
        arr = mergeSort(arr);
        System.out.print((long)count);

    }
}