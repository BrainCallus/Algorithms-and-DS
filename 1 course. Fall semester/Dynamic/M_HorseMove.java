import java.util.Arrays;
import java.util.Scanner;

public class M_HorseMove {
    static int n;
    static int[][] dp;
    static final int MOD = 1000000000;

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        dp = new int[n + 1][10];
        Arrays.fill(dp[1], 1);
        dp[1][0] = dp[1][8] = 0;
        for (int i = 2; i <= n; i++) {
            dp[i][0] += (dp[i - 1][4] + dp[i - 1][6]) % MOD;
            dp[i][1] += (dp[i - 1][6] + dp[i - 1][8]) % MOD;
            dp[i][2] += (dp[i - 1][7] + dp[i - 1][9]) % MOD;
            dp[i][3] += (dp[i - 1][4] + dp[i - 1][8]) % MOD;
            dp[i][4] += (dp[i - 1][0] + dp[i - 1][3]) % MOD;
            dp[i][4] %= MOD;
            dp[i][4] += dp[i - 1][9] % MOD;
            dp[i][6] += (dp[i - 1][0] + dp[i - 1][1]) % MOD;
            dp[i][6] %= MOD;
            dp[i][6] += dp[i - 1][7] % MOD;
            dp[i][7] += (dp[i - 1][2] + dp[i - 1][6]) % MOD;
            dp[i][8] += (dp[i - 1][1] + dp[i - 1][3]) % MOD;
            dp[i][9] += (dp[i - 1][2] + dp[i - 1][4]) % MOD;
            for (int j = 0; j < 10; j++) {
                dp[i][j] %= MOD;
            }
        }
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            sum += dp[n][i];
            sum %= MOD;
        }
        System.out.println(sum);
    }

}
