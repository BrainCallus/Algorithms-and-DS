import java.util.ArrayList;
import java.util.Scanner;

public class E_PostfixSpell {
    static ArrayList<Integer> stack;

    static int intParse(int ind, String s) {
        int num = Integer.parseInt(String.valueOf(s.charAt(ind++)));
        while (true) {
            char ch = s.charAt(ind++);
            if (ch < '0' || ch > '9') {
                break;
            }
            num = num * 10 + Integer.parseInt(String.valueOf(ch));
        }
        return num;
    }

    public static void main(String[] args) {
        stack = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        String expr = scanner.nextLine();

        for (int i = 0; i < expr.length(); i++) {
            switch (expr.charAt(i)) {
                case ' ' -> {
                }
                case '+' -> {
                    int term1 = stack.remove(stack.size() - 1);
                    int term2 = stack.remove(stack.size() - 1);
                    stack.add(term2 + term1);
                }
                case '-' -> {
                    int term1 = stack.remove(stack.size() - 1);
                    int term2 = stack.remove(stack.size() - 1);
                    stack.add(term2 - term1);
                }
                case '*' -> {
                    int term1 = stack.remove(stack.size() - 1);
                    int term2 = stack.remove(stack.size() - 1);
                    stack.add(term2 * term1);
                }
                default -> stack.add(intParse(i, expr));

            }

        }
        System.out.println(stack.remove(stack.size() - 1));
    }
}
