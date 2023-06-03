import java.util.Scanner;

public class G_DSU {

    static int n;
    static int[] ancestor, min, max, size, rank;

    static void build() {
        for (int i = 0; i <= n; i++) {
            ancestor[i] = min[i] = max[i] = i;
            size[i] = rank[i] = 1;
        }
    }

    static void union(int x, int y) {
        x = find(x);
        y = find(y);
        if (rank[x] < rank[y]) {
            int tmp = x;
            x = y;
            y = tmp;
        }
        if (x != y) {
            size[x] += size[y];
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
        }
        ancestor[y] = x;
        max[x] = Math.max(max[x], max[y]);
        min[x] = Math.min(min[x], min[y]);

    }

    static void get(int x) {
        x = find(x);
        System.out.println(min[x] + " " + max[x] + " " + size[x]);
    }

    static int find(int x) {
        if (ancestor[x] != x) {
            ancestor[x] = find(ancestor[x]);
        }
        return ancestor[x];
    }

    static void init() {
        ancestor = new int[n + 1];
        min = new int[n + 1];
        max = new int[n + 1];
        size = new int[n + 1];
        rank = new int[n + 1];
        build();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        init();
        String[] operation;
        while (scanner.hasNext()) {
            operation = scanner.nextLine().split(" ");
            if (operation[0].equals("union")) {
                union(Integer.parseInt(operation[1]), Integer.parseInt(operation[2]));
            } else if (operation[0].equals("get")) {
                get(Integer.parseInt(operation[1]));
            }
        }
    }

}
