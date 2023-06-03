import java.util.Scanner;

public class N_Levenshtein {
    static int[][] changes;

    static int minTriple(int a, int b, int c) {
        int min = Math.min(a, b);
        min = Math.min(min, c);
        return min;
    }

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        char[] first = (" " + scanner.nextLine()).toCharArray();
        char[] second = (" " + scanner.nextLine()).toCharArray();
        int lenF = first.length, lenS = second.length;
        changes = new int[lenF + 1][lenS + 1];
        for (int i = 1; i <= lenF; i++) {
            changes[i][0] = i;
        }
        for (int i = 1; i <= lenS; i++) {
            changes[0][i] = i;
        }
        for (int i = 1; i < lenF; i++) {
            for (int j = 1; j < lenS; j++) {
                if (first[i] == second[j]) {
                    changes[i][j] = changes[i - 1][j - 1];
                } else {
                    changes[i][j] = minTriple(changes[i - 1][j - 1], changes[i][j - 1], changes[i - 1][j]) + 1;
                }
            }
        }
        System.out.println(changes[lenF - 1][lenS - 1]);

    }

}
