import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public
class C_Astrograd {
    public

    static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[]
                idInd = new int[200000];
        Arrays.fill(idInd, -1);
        ArrayList<Integer> queue = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            switch (scanner.nextInt()) {
                case 1 -> {
                    queue.add(scanner.nextInt());
                    idInd[queue.get(queue.size() - 1)] = queue.size() - 1;
                }
                case 2 -> {
                    for (int j = 1; j < queue.size(); j++) {
                        idInd[queue.get(j)]--;
                    }
                    idInd[queue.get(0)] = -1;
                    queue.remove(0);
                }
                case 3 -> {
                    idInd[queue.get(queue.size() - 1)] = -1;
                    queue.remove(queue.size() - 1);
                }
                case 4 -> System.out.println(idInd[scanner.nextInt()]);
                case 5 -> System.out.println(queue.get(0));
            }
        }
    }
}