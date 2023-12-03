import java.util.Scanner;

public class H_Avia {
    static boolean[] mark;
    static boolean[][] gr;
    static int[][] consumption;
    static int n;

    static void rout(int v, int dir) {
        mark[v] = true;
        for (int i = 0; i < n; i++) {
            if (!mark[i]) {
                if (dir == 1 && gr[v][i]) rout(i, dir);
                else if (dir == -1 && gr[i][v]) rout(i, dir);
            }
        }
    }

    static boolean allMarked() {
        for (boolean b : mark) {
            if (!b) return false;
        }
        return true;
    }

    static boolean check() {
        if (allMarked()) {
            mark = new boolean[n];
            rout(0, -1);
            return allMarked();
        }
        return false;
    }

    static int optCons() {
        int l = 0, r = 1000000001;
        mark = new boolean[n];
        while (l < r) {
            int m = l + (r - l) / 2;

            for (int i = 0; i < consumption.length; i++) {
                for (int j = 0; j < consumption.length; j++) {
                    gr[i][j] = (consumption[i][j] <= m);
                }
            }
            mark = new boolean[n];
            rout(0, 1);
            if (allMarked()) {
                mark = new boolean[n];
                rout(0, -1);
                if (!allMarked()) l = m + 1;
                else r = m;
            } else {
                l = m + 1;
            }
            if (!check()) l = m + 1;
            else r = m;

        }
        return l;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        consumption = new int[n][];
        gr = new boolean[n][];
        for (int i = 0; i < n; i++) {
            gr[i] = new boolean[n];
            consumption[i] = new int[n];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                consumption[i][j] = scanner.nextInt();
            }
        }
        System.out.println(optCons());
    }
}
