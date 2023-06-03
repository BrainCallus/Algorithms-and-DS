import java.util.Scanner;

public class K_Turtle {
    static final int INF = 100000000;
    static int n, m;
    static int[][] dp;
    static int[] prev;

    static void init() {
        dp = new int[n + 1][m + 1];
        prev = new int[n * m + 1];
        for (int i = 2; i <= n; i++) {
            dp[i][0] = -INF;
        }
        for (int i = 2; i <= m; i++) {
            dp[0][i] = -INF;
        }
    }

    static void printMoves() {
        System.out.println(dp[n][m]);
        StringBuilder moves = new StringBuilder();
        int ptr = n * m;

        while (ptr > 1) {
            if (ptr - prev[ptr] > 1) {
                moves.insert(0, "D");
            } else {
                moves.insert(0, "R");
            }
            ptr = prev[ptr];
        }
        System.out.println(moves);
    }

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        init();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (dp[i][j - 1] > dp[i - 1][j]) {
                    dp[i][j] = scanner.nextInt() + dp[i][j - 1];
                    prev[m * (i - 1) + j] = m * (i - 1) + j - 1;
                } else {
                    dp[i][j] = dp[i - 1][j] + scanner.nextInt();
                    prev[m * (i - 1) + j] = m * (i - 2) + j;
                }
            }
        }
        printMoves();
    }

}
