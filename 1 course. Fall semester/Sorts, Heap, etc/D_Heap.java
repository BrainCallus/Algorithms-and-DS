import java.util.ArrayList;
import java.util.Scanner;

public class D_Heap {
    static ArrayList<Integer> heap;
    static int n;

    static void swap(int i, int j) {
        int tmp = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, tmp);
    }

    static void sift_up(int i) {
        while (i > 0 && heap.get(i) > heap.get((i - 1) / 2)) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;

        }
    }

    static void insert(int x) {
        heap.add(x);
        sift_up(heap.size() - 1);
    }

    static void sift_down(int i) {
        while (2 * i + 1 < heap.size()) {
            int j = 2 * i + 1;
            if (j + 1 < heap.size() && heap.get(j + 1) > heap.get(j)) {
                j++;
            }
            if (heap.get(i) >= heap.get(j)) {
                break;
            } else {
                swap(i, j);
                i = j;
            }
        }
    }

    static int extractMax() {
        int max = heap.get(0);
        swap(0, heap.size() - 1);
        heap.remove(heap.size() - 1);
        sift_down(0);
        return max;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        heap = new ArrayList<>();
        int command;
        for (int i = 0; i < n; i++) {
            command = scanner.nextInt();
            if (command == 0) {
                insert(scanner.nextInt());
            } else {
                System.out.println(extractMax());
            }
        }
    }
}