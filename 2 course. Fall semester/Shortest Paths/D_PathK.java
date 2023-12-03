import java.util.Scanner;

public class D_PathK {
    static int n, m, k, s;
    static long[][] dist;
    static Rib[] ribs;

    static class Rib {
        private final int start;
        private final int end;
        private final long len;

        public Rib(int start, int end, long len) {
            this.start = start;
            this.end = end;
            this.len = len;
        }
    }

    static void getDistances() {
        for (int i = 1; i <= k; i++) {
            for (Rib rib : ribs) {
                if (dist[rib.start][i - 1] < Integer.MAX_VALUE &&
                        dist[rib.end][i] > dist[rib.start][i - 1] + rib.len) {
                    dist[rib.end][i] = dist[rib.start][i - 1] + rib.len;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (dist[i][k] == Integer.MAX_VALUE) {
                System.out.println(-1);
            } else {
                System.out.println(dist[i][k]);
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        k = scanner.nextInt();
        s = scanner.nextInt();
        dist = new long[n + 1][k + 1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dist[i][j] = Integer.MAX_VALUE;
            }

        }
        dist[s][0] = 0;
        ribs = new Rib[m];
        for (int i = 0; i < m; i++) {
            ribs[i] = new Rib(scanner.nextInt(), scanner.nextInt(), scanner.nextInt());
        }
        getDistances();
    }
}
