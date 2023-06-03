import java.util.Scanner;

public
class B_Balls {
    public

    static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] balls = new int[n];
        int[] dp = new int[n];
        for (int i = 0; i < n; i++) {
            balls[i] = scanner.nextInt();
            dp[i] = 1;
        }
        int delta = 0, index = 0, cnt = 0;
        for (int i = 1; i < n; i++) {
            if (delta + 1 <= i && balls[i] == balls[i - 1 - delta]) {
                dp[i] = dp[index] + 1;
                index = i;
                delta++;
            } else {
                index = i;
                delta = 0;
            }
            if (dp[i] >= 3) {
                while (true) {
                    if (i + 1 < balls.length && balls[i + 1] == balls[i]) {
                        dp[i + 1] = 1 + dp[i++];
                        delta++;
                    } else {
                        break;
                    }
                }
                cnt += dp[i];
                index = i - delta < 0 ? i : i - delta;

                if (delta < i) {
                    delta++;
                    if (dp[i - delta] >= 3 && dp[i] >= delta) {
                        delta += dp[i - delta];
                    }
                    index = i - delta < 0 ? i : i - delta;
                    if (dp[i - delta] == 2) {
                        delta++;
                    }
                }
            }
        }
        System.out.println(cnt);
    }
}