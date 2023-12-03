import java.util.ArrayList;
import java.util.Scanner;

public class E_ShortestPaths {
    static int n, m, s;
    static long[] dist;
    static boolean[] mark;
    static Rib[] ribs;
    static ArrayList[] bonds;


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

    static void dfs(int v) {
        mark[v] = true;
        for (int i = 0; i < bonds[v].size(); i++) {
            int u = (int) bonds[v].get(i);
            if (!mark[u]) {
                dfs(u);
            }
        }
    }

    static void checkNeg() {
        mark = new boolean[n + 1];
        for (int i = 0; i < n; i++) {
            for (Rib rib : ribs) {
                if (!mark[rib.end] && dist[rib.start] < Long.MAX_VALUE &&
                        dist[rib.end] > dist[rib.start] + rib.len) {
                    dfs(rib.end);
                }
            }
        }
    }

    static void getDistances() {
        for (int i = 0; i < n; i++) {
            for (Rib rib : ribs) {
                if (dist[rib.start] < Long.MAX_VALUE &&
                        dist[rib.end] > dist[rib.start] + rib.len) {
                    dist[rib.end] = dist[rib.start] + rib.len;
                }
            }
        }
        checkNeg();

        for (int i = 1; i <= n; i++) {
            if (dist[i] == Long.MAX_VALUE) {
                System.out.println("*");
            } else if (mark[i]) {
                System.out.println("-");
            } else {
                System.out.println(dist[i]);
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        s = scanner.nextInt();
        dist = new long[n + 1];
        bonds = new ArrayList[n + 1];
        for (int i = 0; i <= n; i++) {
            dist[i] = Long.MAX_VALUE;
            bonds[i] = new ArrayList();
        }
        dist[s] = 0;
        ribs = new Rib[m];

        for (int i = 0; i < m; i++) {
            ribs[i] = new Rib(scanner.nextInt(), scanner.nextInt(), scanner.nextLong());
            bonds[ribs[i].start].add(ribs[i].end);
        }
        getDistances();
    }
}
