import java.util.Scanner;

public class Q_Dominoes {
    static int n, m;
    static int[][] cells;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();

        cells = new int[n + 1][m + 1];
        long[][][] dp = new long[m + 1][n + 1][(1 << n) + 1];
        String prom = scanner.nextLine();
        for (int i = 0; i < n; i++) {
            prom = scanner.nextLine();
            for (int j = 0; j < m; j++) {
                if (prom.charAt(j) == 'X') {
                    cells[i][j] = 1;

                }
            }
        }
        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int p = 0; p < (1 << n); p++) {
                    if (cells[j][i] == 0) {
                        if ((p & (1 << j)) > 0) {
                            dp[i][j + 1][p - (1 << j)] += dp[i][j][p];

                        } else {
                            if (cells[j][i + 1] == 0) dp[i][j + 1][p + (1 << j)] += dp[i][j][p];
                            if (j < n - 1 && (p & (1 << (j + 1))) == 0 && cells[j + 1][i] == 0) {
                                dp[i][j + 1][p + (1 << (j + 1))] += dp[i][j][p];
                            }
                        }
                    } else {
                        if ((p & (1 << j)) > 0) {
                            dp[i][j + 1][p - (1 << j)] += dp[i][j][p];
                        } else {
                            dp[i][j + 1][p] += dp[i][j][p];
                        }
                    }
                }
            }
            for (int p = 0; p < (1 << n); p++) {
                dp[i + 1][0][p] = dp[i][n][p];
            }
        }
        System.out.println(dp[m][0][0]);
    }

}
