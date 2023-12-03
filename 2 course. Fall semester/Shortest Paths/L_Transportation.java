import java.util.Arrays;
import java.util.Scanner;

public class L_Transportation {
    static int n, m;
    static long[] dist;
    static Rib[] ribs;
    static final int TL = 1440;
    static final int DEFAULT_TRUCK_W = 3000000;
    static final int DEFAULT_CUP_W = 100;
    static final int NOROAD = Integer.MAX_VALUE;

    static class Rib {
        private final int start;
        private final int end;
        private final int time;

        private final long capacity;

        public Rib(int start, int end, int time, long capacity) {
            this.start = start;
            this.end = end;
            this.time = time;
            this.capacity = capacity;
        }
    }

    static void getDistances(int amount) {
        int curW = DEFAULT_TRUCK_W + amount * DEFAULT_CUP_W;
        boolean flag = false;
        while (!flag) {
            flag = true;
            for (Rib rib : ribs) {
                if (curW <= rib.capacity) {
                    if (dist[rib.end] > dist[rib.start] + rib.time) {
                        flag = false;
                        dist[rib.end] = dist[rib.start] + rib.time;
                    }
                    if (dist[rib.start] > dist[rib.end] + rib.time) {
                        flag = false;
                        dist[rib.start] = dist[rib.end] + rib.time;
                    }
                }
            }
        }
    }

    static void maxCups(int maxAmount) {
        int l = 0, r = maxAmount + 1;
        while (r - l > 1) {
            Arrays.fill(dist, NOROAD);
            dist[0] = 0;
            int m = l + (r - l) / 2;
            getDistances(m);
            if (dist[n - 1] <= TL) {
                l = m;
            } else {
                r = m;
            }
        }
        System.out.println(l);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        dist = new long[n];
        ribs = new Rib[m];
        int max = 0;
        for (int i = 0; i < m; i++) {
            ribs[i] = new Rib(scanner.nextInt() - 1, scanner.nextInt() - 1, scanner.nextInt(), scanner.nextLong());
            if (ribs[i].capacity > max) max = (int) ribs[i].capacity;
        }
        maxCups((max - DEFAULT_TRUCK_W) / 100);
    }
}
