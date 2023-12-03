import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;


public class J_SpanTree2 {
    static int n, m;
    static ArrayList<Ribs> ribs;
    static int[] ancec;
    static int[] rank;

    static class Ribs {
        private final int first;
        private final int second;
        private final long weight;

        public Ribs(int first, int second, long weight) {
            this.first = first;
            this.second = second;
            this.weight = weight;
        }

        public long getWeight() {
            return this.weight;
        }


    }

    static int find(int x) {
        if (ancec[x] != x) ancec[x] = find(ancec[x]);
        return ancec[x];
    }

    static void union(int x, int y) {
        x = find(x);
        y = find(y);
        if (rank[x] > rank[y]) {
            int tmp = x;
            x = y;
            y = tmp;
        }
        ancec[x] = y;
        if (rank[x] == rank[y]) rank[y]++;
    }

    static void minWeight() {
        long minW = 0;

        for (int i = 0; i < m; i++) {
            Ribs rib = ribs.get(i);
            if (find(rib.first) != find(rib.second)) {
                minW += rib.weight;
                union(rib.first, rib.second);
            }
        }
        System.out.println(minW);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        ribs = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            ribs.add(new Ribs(scanner.nextInt(), scanner.nextInt(), scanner.nextLong()));
        }
        ancec = new int[n + 1];
        rank = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            ancec[i] = i;
            rank[i] = 1;
        }
        ribs.sort(Comparator.comparing(Ribs::getWeight));
        minWeight();
    }
}