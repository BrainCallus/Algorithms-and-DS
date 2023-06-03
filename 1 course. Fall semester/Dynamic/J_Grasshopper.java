import java.util.ArrayList;
import java.util.Scanner;

public class J_Grasshopper {
    static int n, k;
    static int[] dp, ancestor;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        k = scanner.nextInt();
        dp = new int[n + 1];
        ancestor = new int[n + 1];

        for (int i = 2; i <= n; i++) {
            int max = Integer.MIN_VALUE;
            for (int j = 1; j <= k; j++) {
                if (i - j < 1) {
                    break;
                }
                if (dp[i - j] > max) {
                    max = dp[i - j];
                    ancestor[i] = i - j;
                }
            }
            dp[i] = i == n ? max : scanner.nextInt() + max;
        }
        ArrayList<Integer> jumps = new ArrayList<>();
        jumps.add(n);
        int ptr = n;
        while (ptr > 1) {
            jumps.add(ancestor[ptr]);
            ptr = ancestor[ptr];
        }
        System.out.println(dp[n]);
        System.out.println(jumps.size() - 1);
        while (!jumps.isEmpty()) {
            System.out.print(jumps.remove(jumps.size() - 1) + " ");
        }

    }

}
