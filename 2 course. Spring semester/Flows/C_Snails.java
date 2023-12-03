import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class C_Snails {

    static int n, m, SRC, DRAIN;
    static int[] dist, unused;
    static ArrayList<Integer> path;
    static ArrayList<Rib>[] bonds;
    static ArrayList<Rib> ribs;
    static final int UNDEF = 2000000000;

    static class Rib {
        private final int end;
        private final long cap;
        private long flow = 0;
        private Rib inverted = null;
        private boolean mark = false;

        public Rib(int end, long cap) {
            this.end = end;
            this.cap = cap;
        }
    }

    static void setInverted(int A, int B) {
        bonds[A].get(bonds[A].size() - 1).inverted = bonds[B].get(bonds[B].size() - 1);
        bonds[B].get(bonds[B].size() - 1).inverted = bonds[A].get(bonds[A].size() - 1);
    }

    static boolean bfs() {
        Arrays.fill(dist, UNDEF);
        dist[SRC] = 0;
        ArrayList<Integer> queue = new ArrayList<>();
        queue.add(SRC);
        while (!queue.isEmpty()) {
            int v = queue.remove(0);
            for (int i = 0; i < bonds[v].size(); i++) {
                Rib rib = bonds[v].get(i);
                if (dist[rib.end] == UNDEF && rib.cap > rib.flow) {
                    dist[rib.end] = dist[v] + 1;
                    queue.add(rib.end);
                }
            }
        }
        return dist[DRAIN] != UNDEF;
    }

    static long dfs(int v, long flow) {
        if (flow == 0 || v == DRAIN) {
            return flow;
        }
        while (unused[v] < bonds[v].size()) {
            Rib rib = bonds[v].get(unused[v]);
            if (dist[rib.end] == dist[v] + 1) {
                long delta = dfs(rib.end, Long.min(flow, rib.cap - rib.flow));
                if (delta != 0) {
                    rib.flow += delta;
                    rib.inverted.flow -= delta;
                    return delta;
                }
            }
            unused[v]++;
        }
        return 0;
    }

    static long maxFlowDinic() {
        int flow = 0;
        while (bfs()) {
            unused = new int[n];
            long f;
            while ((f = dfs(SRC, UNDEF)) != 0) {
                flow += f;
            }
        }
        return flow;
    }

    static void getPath(int v) {
        path.add(v);
        if (v == DRAIN) {
            return;
        }
        for (int i = 0; i < bonds[v].size(); i++) {
            Rib rib = bonds[v].get(i);
            if (!rib.mark && rib.flow == 1) {
                rib.mark = true;
                rib.inverted.mark = true;

                getPath(rib.end);
                break;
            }
        }
    }

    static void print(List<Integer> path) {
        for (Integer vertex : path) {
            System.out.print(vertex + 1 + " ");
        }
        System.out.println();
    }

    static void printFlows(long flow) {
        if (flow < 2) {
            System.out.println("NO");
        } else {
            System.out.println("YES");
            for (int i = 0; i < 2; i++) {
                path = new ArrayList<>();
                getPath(SRC);
                print(path);
            }
        }
    }

    static void init() {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        SRC = scanner.nextInt() - 1;
        DRAIN = scanner.nextInt() - 1;
        dist = new int[n];
        unused = new int[n];
        bonds = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            bonds[i] = new ArrayList<>();
        }
        ribs = new ArrayList<>();
        int A, B;
        for (int i = 0; i < m; i++) {
            A = scanner.nextInt() - 1;
            B = scanner.nextInt() - 1;
            bonds[A].add(new Rib(B, 1));
            bonds[B].add(new Rib(A, 0));
            setInverted(A, B);
            ribs.add(bonds[A].get(bonds[A].size() - 1));
        }
    }

    public static void main(String[] args) {
        init();
        printFlows(maxFlowDinic());
    }
}
