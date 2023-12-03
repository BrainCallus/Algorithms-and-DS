import java.util.Scanner;

public class B_ShortestPath2 {
    static int n, m;
    static int[] dist;
    static Rib[] ribs;

    static class Rib {
        private final int start;
        private final int end;
        private final int len;

        public Rib(int start, int end, int len) {
            this.start = start;
            this.end = end;
            this.len = len;
        }
    }

    static void getDistances() {
        boolean flag = false;
        while (!flag) {
            flag = true;
            for (Rib rib : ribs) {
                int u = rib.start, v = rib.end, d = rib.len;
                if (dist[v] > dist[u] + d) {
                    flag = false;
                    dist[v] = dist[u] + d;
                }
                if (dist[u] > dist[v] + d) {
                    flag = false;
                    dist[u] = dist[v] + d;
                }

            }
        }
        for (int i = 0; i < n; i++) {
            System.out.print(dist[i] + " ");
        }
    }

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        dist = new int[n];
        for (int i = 0; i < n; i++) {
            dist[i] = 400001;
        }
        dist[0] = 0;
        ribs = new Rib[m];
        for (int i = 0; i < m; i++) {
            int s = scanner.nextInt() - 1, e = scanner.nextInt() - 1, w = scanner.nextInt();
            ribs[i] = new Rib(s, e, w);
        }
        getDistances();
    }
}
