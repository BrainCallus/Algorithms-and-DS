import java.util.Scanner;

public class A_SimpleSort {
    static int n;
    static int[] arr;

    static void fill(int[] source, int[] target, int start, int finish) {
        if (finish >= 0) System.arraycopy(source, start, target, 0, finish);

    }

    static int[] merge(int[] a, int[] b) {
        int i = 0, j = 0;
        int[] c = new int[a.length + b.length];
        while (i < a.length || j < b.length) {
            if (j == b.length || i < a.length && a[i] < b[j]) {
                c[i + j] = a[i++];
            } else {
                c[i + j] = b[j++];
            }
        }
        return c;
    }

    static int[] mergeSort(int[] mas) {
        int len = mas.length;
        if (len <= 1) return mas;
        int[] l = new int[len / 2];
        int[] r = new int[len - len / 2];
        fill(mas, l, 0, len / 2);
        fill(mas, r, len / 2, len - len / 2);
        l = mergeSort(l);
        r = mergeSort(r);
        return merge(l, r);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }
        arr = mergeSort(arr);
        for (int j : arr) {
            System.out.print(j + " ");
        }
    }
}