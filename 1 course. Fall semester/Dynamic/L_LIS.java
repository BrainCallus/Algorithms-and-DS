import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class L_LIS {
    static int n;
    static int[] len, arr, prev;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        len = new int[n];
        arr = new int[n];
        prev = new int[n];
        Arrays.fill(prev, -1);
        int maxLenInd = -1, maxLen = 0;
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
            len[i] = 1;
            for (int j = 0; j < i; j++) {
                if (arr[i] > arr[j] && len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    prev[i] = j;
                }
            }
            if (len[i] > maxLen) {
                maxLen = len[i];
                maxLenInd = i;
            }
        }
        System.out.println(maxLen);
        ArrayList<Integer> LIS = new ArrayList<>();
        int ptr = maxLenInd;
        for (int i = 0; i < maxLen; i++) {
            LIS.add(arr[ptr]);
            ptr = prev[ptr];
        }
        while (!LIS.isEmpty()) {
            System.out.print(LIS.remove(LIS.size() - 1) + " ");
        }
    }

}
