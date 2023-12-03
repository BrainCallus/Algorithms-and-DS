import java.util.ArrayList;
import java.util.Scanner;

public class I_Grandy {

    static int n, m;
    static ArrayList<Integer>[] bonds;
    static boolean[] mark;
    static int[] grandy;
    static ArrayList<Integer> topsort;

    static void dfs(int v) {
        mark[v] = true;
        for (int i = 0; i < bonds[v].size(); i++) {
            int u = bonds[v].get(i);
            if (!mark[u]) {
                dfs(u);
            }
        }
        topsort.add(v);
    }

    static void init() {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        bonds = new ArrayList[n];
        mark = new boolean[n];
        grandy = new int[n];
        topsort = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            bonds[i] = new ArrayList<>();
        }
        for (int i = 0; i < m; i++) {
            bonds[scanner.nextInt() - 1].add(scanner.nextInt() - 1);
        }
    }

    static void findGrandy() {
        for (int i = 0; i < bonds.length; i++) {
            if (!mark[i]) {
                dfs(i);
            }
        }

        for (int i = 0; i < n; i++) {
            int v = topsort.get(i);
            mark = new boolean[n];
            for (int j = 0; j < bonds[v].size(); j++) {
                mark[grandy[bonds[v].get(j)]] = true;
            }
            for (int j = 0; j < n; j++) {
                if (!mark[j]) {
                    grandy[v] = j;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            System.out.println(grandy[i]);
        }
    }

    public static void main(String[] args) {
        init();
        findGrandy();
    }
}
