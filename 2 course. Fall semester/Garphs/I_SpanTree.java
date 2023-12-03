import java.util.Scanner;

public class I_SpanTree {
    static boolean[] added;
    static int n = 0;
    static Peac[] PEACS;

    static class Peac {
        private final int x;
        private final int y;
        private double nearest;
        private int next;

        public Peac(int x, int y) {
            this.x = x;
            this.y = y;
            this.nearest = 1000000000;
            this.next = -1;
        }

        public void setNearest(double nearest) {
            this.nearest = nearest;
        }

        public void setNext(int next) {
            this.next = next;
        }

    }

    static double dist(Peac a, Peac b) {
        return Math.sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    static double minWeight() {
        double weight = 0;
        for (int i = 0; i < n; i++) {
            int p = -1;
            for (int j = 0; j < n; j++) {
                if (!added[j] && (p == -1 || PEACS[j].nearest < PEACS[p].nearest)) {
                    p = j;
                }
            }
            added[p] = true;
            if (PEACS[p].next != -1) {
                weight += dist(PEACS[p], PEACS[PEACS[p].next]);
            }
            for (int v = 0; v < n; v++) {
                double minW = dist(PEACS[p], PEACS[v]);
                if (minW < PEACS[v].nearest) {
                    PEACS[v].setNearest(minW);
                    PEACS[v].setNext(p);
                }
            }
        }
        return weight;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        PEACS = new Peac[n];
        added = new boolean[n];
        for (int i = 0; i < n; i++) {
            PEACS[i] = new Peac(scanner.nextInt(), scanner.nextInt());
        }
        PEACS[0].setNearest(0);
        scanner.close();

        if (n > 1) System.out.printf("%.5f", minWeight());
        else System.out.printf("%.5f", 0.0);
    }
}