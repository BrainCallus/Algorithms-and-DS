import java.util.*;

public class A_JustFlow {

    static int n, m, SRC, DRAIN;
    static int[] dist, unused;
    static ArrayList<Rib>[] bonds;
    static Rib[] ribs;
    static final int UNDEF = 2000000000;

    static class Rib {
    private final int end;
    private final long cap;
    private long flow = 0;
    private Rib inverted = null;

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

    static void printFlows(long flow) {
        System.out.println(flow);
        for (int i = 0; i < m; i++) {
            System.out.println( ribs[i].flow);
        }
    }

    static void init() {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        dist = new int[n];
        unused = new int[n];
        bonds = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            bonds[i] = new ArrayList<>();
        }
        ribs = new Rib[m];
        int A, B;
        long C;
        for (int i = 0; i < m; i++) {
            A = scanner.nextInt() - 1;
            B = scanner.nextInt() - 1;
            C = scanner.nextLong();
            bonds[A].add(new Rib(B, C));
            bonds[B].add(new Rib(A, C));
            setInverted(A, B);
            ribs[i] = bonds[A].get(bonds[A].size() - 1);
        }
        SRC = 0;
        DRAIN = n - 1;
    }

public static void main(String[] args) {
        init();
        printFlows(maxFlowDinic());
    }
}
