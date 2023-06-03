import java.util.Scanner;

public class B_CountingSort {
    static int n;
    static int[] countingArr;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        countingArr = new int[101];
        for (int i = 0; i < n; i++) {
            countingArr[scanner.nextInt()]++;
        }

        for (int i = 0; i < 101; i++) {
            if (countingArr[i] > 0) {
                for (int j = 0; j < countingArr[i]; j++) {
                    System.out.print(i + " ");
                }
            }
        }
    }
}