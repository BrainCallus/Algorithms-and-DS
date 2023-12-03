import java.util.Scanner;

public class A_Floyd {
    static int n;
    static int[][] bonds;
    static int[][] dist;

    static void getDistances() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(dist[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        bonds = new int[n][];
        dist = new int[n][];
        for (int i = 0; i < n; i++) {
            bonds[i] = new int[n];
            dist[i] = new int[n];
            for (int j = 0; j < n; j++) {
                bonds[i][j] = scanner.nextInt();
                dist[i][j] = bonds[i][j];
            }
        }
        getDistances();
    }
}
