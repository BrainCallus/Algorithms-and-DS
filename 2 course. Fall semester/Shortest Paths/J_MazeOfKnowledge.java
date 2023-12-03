import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Scanner;

public class J_MazeOfKnowledge {

    static int n, m;
    static long[] dist;
    static boolean[] mark;
    static ArrayList[] bonds;
    static Rib[] ribs;
    static final long NOROAD = (long) 1000000 * 1000000;

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

    static void writeAns(String answ) {
        try {
            try (BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(
                    new FileOutputStream("maze.out"), StandardCharsets.UTF_8))) {
                writer.write(answ);
            }

        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    static void dfs(int v) {
        mark[v] = true;
        for (int i = 0; i < bonds[v].size(); i++) {
            if (!mark[(int) bonds[v].get(i)]) {
                dfs((int) bonds[v].get(i));
            }
        }

    }

    static void checkNeg() {
        mark = new boolean[n];
        for (int i = 0; i < n; i++) {
            for (Rib rib : ribs) {
                if (!mark[rib.end] && dist[rib.start] < NOROAD &&
                        dist[rib.end] > dist[rib.start] + rib.len) {
                    dfs(rib.end);
                }
            }
        }
    }

    static void getDistances() {
        for (int i = 0; i < n; i++) {
            for (Rib rib : ribs) {
                int u = rib.start, v = rib.end;
                long d = rib.len;
                if (dist[u] < NOROAD && dist[v] > dist[u] + d) {
                    dist[v] = Math.max(dist[u] + d, -NOROAD);
                }

            }
        }
        checkNeg();
        String answ;

        if (dist[n - 1] == NOROAD) {
            answ = ":(";
        } else if (mark[n - 1]) {
            answ = ":)";
        } else {
            answ = String.valueOf(dist[n - 1] * -1);
        }
        writeAns(answ);

    }

    static void init() {
        try {
            FileReader reader = new FileReader("maze.in");

            Scanner scanner = new Scanner(reader);
            n = scanner.nextInt();
            bonds = new ArrayList[n];
            dist = new long[n];
            for (int i = 0; i < n; i++) {
                bonds[i] = new ArrayList();
                dist[i] = NOROAD;
            }
            dist[0] = 0;

            m = scanner.nextInt();
            ribs = new Rib[m];
            for (int i = 0; i < m; i++) {
                int s = scanner.nextInt() - 1, e = scanner.nextInt() - 1;
                long w = scanner.nextLong();
                ribs[i] = new Rib(s, e, -1 * w);
                bonds[s].add(e);
            }

        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        init();
        getDistances();
    }
}
