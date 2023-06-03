import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class F_StackSorting {

    static int n;
    static ArrayList<Integer> stackA, stackB;
    static ArrayList<String> operations;
    static int[][] positions;

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        positions = new int[n + 1][2];
        Arrays.fill(positions[0], -1);
        Arrays.fill(positions[1], -1);
        stackA = new ArrayList<>();
        stackB = new ArrayList<>();
        operations = new ArrayList<>();
        for (int i = n - 1; i >= 0; i--) {
            int el = scanner.nextInt();
            stackA.add(0, el);
            positions[el][0] = i;
        }
        for (int i = 1; i <= n; i++) {
            if (positions[i][0] != -1) {
                int cur;
                do {
                    cur = stackA.remove(stackA.size() - 1);
                    positions[cur][0] = -1;
                    positions[cur][1] = stackB.size();
                    stackB.add(cur);
                    operations.add("push");
                } while (cur != i);
            }

            if (positions[i][1] != stackB.size() - 1) {
                operations.add("impossible");
                break;
            } else {
                stackB.remove(stackB.size() - 1);
                operations.add("pop");
            }

        }
        if (operations.get(operations.size() - 1).equals("impossible")) {
            System.out.println("impossible");
        } else {
            for (String operation : operations) {
                System.out.println(operation);
            }
        }
    }

}
