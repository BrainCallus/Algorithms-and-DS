import java.util.Scanner;

public class J_K_Best {
    static int n, k;
    static Jew[] arr;


    static class Jew {
        private final int numb;
        private final int value;
        private final int weight;
        private double bal;

        public Jew(int numb, int value, int weight) {
            this.numb = numb;
            this.value = value;
            this.weight = weight;
        }

        public void setBal(double awer) {
            this.bal = awer;
        }

    }

    static void fill(Jew[] source, Jew[] target, int start, int finish) {
        if (finish >= 0) System.arraycopy(source, start, target, 0, finish);
    }

    static Jew[] merge(Jew[] a, Jew[] b) {
        int i = 0, j = 0;
        Jew[] c = new Jew[a.length + b.length];
        while (i < a.length || j < b.length) {
            if (j == b.length || i < a.length && a[i].bal > b[j].bal) {
                c[i + j] = a[i++];
            } else {
                c[i + j] = b[j++];
            }
        }
        return c;
    }

    static Jew[] mergeSort(Jew[] mas) {
        int len = mas.length;
        if (len <= 1) return mas;
        Jew[] l = new Jew[len / 2];
        Jew[] r = new Jew[len - len / 2];
        fill(mas, l, 0, len / 2);
        fill(mas, r, len / 2, len - len / 2);
        l = mergeSort(l);
        r = mergeSort(r);
        return merge(l, r);
    }

    static double sum(double cursum) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            arr[i].setBal(arr[i].value - arr[i].weight * cursum);
        }
        arr = mergeSort(arr);
        for (int i = 0; i < k; i++) {
            sum += arr[i].bal;
        }
        return sum;
    }

    static void optSum() {
        double l = 0.0, r = 10000001;
        while (r - l > 0.0000001) {
            double m = l + (r - l) / 2;
            if (sum(m) >= 0) {
                l = m;
            } else r = m;
        }
        for (int i = 0; i < k; i++) {
            System.out.println(arr[i].numb);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        k = scanner.nextInt();
        arr = new Jew[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new Jew(i + 1, scanner.nextInt(), scanner.nextInt());
        }
        optSum();
    }
}