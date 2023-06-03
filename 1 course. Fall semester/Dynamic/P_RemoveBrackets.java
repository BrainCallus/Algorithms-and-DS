import java.util.Scanner;

public class P_RemoveBrackets {

    static char[] sequence;
    static String good;
    static int[][] dp, prev;

    static boolean goodPair(int lInd, int rInd) {
        return (sequence[lInd] == '(' && sequence[rInd] == ')') || (sequence[lInd] == '{' && sequence[rInd] == '}')
                || (sequence[lInd] == '[' && sequence[rInd] == ']');
    }

    static void recover(int lInd, int rInd) {
        if (rInd - lInd == dp[lInd][rInd] - 1) return;
        if (dp[lInd][rInd] == 0) {
            good += String.valueOf(sequence).substring(lInd, rInd + 1);
        } else if (prev[lInd][rInd] == -1) {
            good += sequence[lInd];
            recover(lInd + 1, rInd - 1);
            good += sequence[rInd];
        } else {
            recover(lInd, prev[lInd][rInd]);
            recover(prev[lInd][rInd] + 1, rInd);
        }
    }

    static void evaluate() {
        for (int r = 0; r < sequence.length; r++) {
            for (int l = r - 1; l >= 0; l--) {
                int minRem = sequence.length;
                int minInd = -1;
                if (goodPair(l, r)) {
                    minRem = dp[l + 1][r - 1];
                }
                for (int k = l; k < r; k++) {
                    if (dp[l][k] + dp[k + 1][r] < minRem) {
                        minRem = dp[l][k] + dp[k + 1][r];
                        minInd = k;
                    }
                }
                dp[l][r] = minRem;
                prev[l][r] = minInd;
            }
        }
    }

    static void getPSP() {
        dp = new int[sequence.length][sequence.length];
        prev = new int[sequence.length][sequence.length];
        for (int i = 0; i < sequence.length; i++) {
            dp[i][i] = 1;
        }
        evaluate();
        recover(0, sequence.length - 1);
        System.out.println(good);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        good = "";
        sequence = scanner.nextLine().toCharArray();
        getPSP();
    }

}
