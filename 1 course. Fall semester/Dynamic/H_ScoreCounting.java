import java.util.Scanner;

public class H_ScoreCounting {

    static int n, m;
    static int[] ancestor, score, rank;

    static void build() {
        for (int i = 0; i <= n; i++) {
            ancestor[i] = i;
            score[i] = 0;
            rank[i] = 1;
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
            score[y] -= score[x];
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
        }
        ancestor[y] = x;

    }

    static int get(int x) {
        int sc = score[x];
        if (x != ancestor[x]) {
            sc += get(ancestor[x]);
        }
        return sc;
    }

    static void add(int team, int val) {
        team = find(team);
        score[team] += val;
    }

    static int find(int x) {
        if (ancestor[x] != x) {
            return find(ancestor[x]);
        }
        return x;
    }

    static void init() {
        ancestor = new int[n + 1];
        score = new int[n + 1];
        rank = new int[n + 1];
        build();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        init();
        String[] operation;
        for (int i = 0; i <= m; i++) {
            operation = scanner.nextLine().split(" ");
            if (operation[0].equals("join")) {
                union(Integer.parseInt(operation[1]), Integer.parseInt(operation[2]));
            } else if (operation[0].equals("add")) {
                add(Integer.parseInt(operation[1]), Integer.parseInt(operation[2]));
            } else if (operation[0].equals("get")) {
                System.out.println(get(Integer.parseInt(operation[1])));
            }
        }
    }

}
