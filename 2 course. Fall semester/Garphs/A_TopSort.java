import java.util.ArrayList;
import java.util.Scanner;

public class A_TopSort {
    static ArrayList[] bonds;
    static boolean[] mark;
    static int[] cyclarr;
    static ArrayList<Integer> topSortQ;

    static void dfs(int v) {
        mark[v] = true;

        for (int i = 0; i < bonds[v].size(); i++) {
            int u = (int) bonds[v].get(i);
            if (!mark[u]) dfs(u);
        }
        topSortQ.add(v);

    }

    static boolean checkCycle(int v) {
        cyclarr[v] = 1;
        for (int i = 0; i < bonds[v].size(); i++) {
            int u = (int) bonds[v].get(i);
            if (cyclarr[u] == 1) return true;
            else if (cyclarr[u] == 0) {
                if (checkCycle(u)) return true;
            }
        }
        cyclarr[v] = 2;
        return false;
    }

    static boolean hasCycle() {
        cyclarr = new int[bonds.length];
        for (int i = 1; i < bonds.length; i++) {
            if (checkCycle(i)) return true;
        }
        return false;
    }

    static void topSort() {
        for (int i = 1; i < bonds.length; i++) {
            if (!mark[i]) {
                dfs(i);
            }
        }
        for (int i = topSortQ.size() - 1; i >= 0; i--) {
            System.out.print(topSortQ.get(i) + " ");
        }
    }


    public static void main(String[] args) {
        topSortQ = new ArrayList<>();
        int n, m;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        mark = new boolean[n + 1];
        bonds = new ArrayList[n + 1];
        for (int i = 0; i <= n; i++) {
            bonds[i] = new ArrayList<>();
        }

        for (int i = 0; i < m; i++) {
            int peac, child;
            peac = scanner.nextInt();
            child = scanner.nextInt();
            bonds[peac].add(child);

        }

        if (!hasCycle()) topSort();
        else System.out.println(-1);

    }
}