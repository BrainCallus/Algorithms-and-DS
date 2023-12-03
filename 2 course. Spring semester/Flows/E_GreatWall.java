import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class E_GreatWall {
    static final long UNDEF = Integer.MAX_VALUE;
    static int m, n;
    static List<List<Cell>> field;
    static Vertex SRC, DRAIN;

    static class Vertex {
        int dist;
        boolean mark = false;
        int unused = 0;
        List<Rib> ribs;

        public Vertex() {
            dist = (int) UNDEF;
            ribs = new ArrayList<>();
        }

        public int getDist() {
            return dist;
        }

        public void setDist(int dist) {
            this.dist = dist;
        }

        public int getUnused() {
            return unused;
        }

        public void drop() {
            dist = (int) UNDEF;
            unused = 0;
        }

        public void buildWall() {
            ribs.get(0).init.setName('+');
        }

        public boolean isSuitable() {
            return !ribs.isEmpty() && ribs.get(0).init.getName() == '.';
        }
    }

    static class Rib {
        long cap;
        long flow = 0;
        Cell init;
        Vertex end;
        Rib inverted;

        public Rib(long cap, Vertex end, Cell init) {
            this.cap = cap;
            this.end = end;
            this.init = init;
        }

        public long getFlow() {
            return flow;
        }

        public void setFlow(long flow) {
            this.flow = flow;
        }

        public long getCap() {
            return cap;
        }

        @SuppressWarnings("BooleanMethodIsAlwaysInverted")
        public boolean isSaturated() {
            return flow == cap;
        }
    }

    static class Cell {
        char name;
        Vertex in;
        Vertex out;

        public Cell(char name) {
            this.name = name;
            in = new Vertex();
            out = new Vertex();
            switch (name) {
                case '.' -> in.ribs.add(new Rib(1, out, this));
                case '-' -> in.ribs.add(new Rib(UNDEF, out, this));
                case 'A' -> {
                    in = null;
                    SRC = out;
                }
                case 'B' -> {
                    out = null;
                    DRAIN = in;
                }
                default -> {
                    in = null;
                    out = null;
                }
            }
        }

        public char getName() {
            return name;
        }

        public void setName(char name) {
            this.name = name;
        }

        public boolean isMountain() {
            return name == '#';
        }

        public void drop() {
            if (in != null) {
                in.drop();
            }
            if (out != null) {
                out.drop();
            }
        }
    }

    static void setInverted(Vertex a, Vertex b) {
        a.ribs.get(a.ribs.size() - 1).inverted = b.ribs.get(b.ribs.size() - 1);
        b.ribs.get(b.ribs.size() - 1).inverted = a.ribs.get(a.ribs.size() - 1);
    }

    static void boundCells(Cell a, Cell b) {
        if (a.isMountain() || b.isMountain()) {
            return;
        }
        if (a.out != null && b.in != null) {
            a.out.ribs.add(new Rib(UNDEF, b.in, a));
            b.in.ribs.add(new Rib(0, a.out, b));
            setInverted(a.out, b.in);
        }
        if (b.out != null && a.in != null) {
            b.out.ribs.add(new Rib(UNDEF, a.in, b));
            a.in.ribs.add(new Rib(0, b.out, a));
            setInverted(b.out, a.in);
        }

    }

    static void dropValues() {
        for (List<Cell> cells : field) {
            for (Cell cell : cells) {
                cell.drop();
            }
        }
    }

    static boolean bfs() {
        dropValues();
        SRC.setDist(0);
        List<Vertex> queue = new ArrayList<>();
        queue.add(SRC);
        while (!queue.isEmpty()) {
            Vertex v = queue.remove(0);
            for (Rib rib : v.ribs) {
                if (rib.end.getDist() == UNDEF && !rib.isSaturated()) {
                    rib.end.setDist(v.dist + 1);
                    queue.add(rib.end);
                }
            }
        }

        return DRAIN.getDist() != UNDEF;
    }

    static long dfs(Vertex v, long curFlow) {
        if (v == DRAIN || curFlow == 0) {
            return curFlow;
        }
        while (v.unused < v.ribs.size()) {
            Rib rib = v.ribs.get(v.getUnused());
            if (rib.end.getDist() == v.getDist() + 1) {
                long delta = dfs(rib.end, Long.min(curFlow, rib.getCap() - rib.getFlow()));
                if (delta != 0) {
                    rib.setFlow(rib.getFlow() + delta);
                    if (rib.inverted != null) {
                        rib.inverted.setFlow(rib.inverted.getFlow() - delta);
                    }
                    return delta;
                }
            }
            v.unused++;
        }
        return 0;
    }

    static long maxFlowDinic() {
        long flow = 0;
        while (bfs()) {
            long f;
            while ((f = dfs(SRC, UNDEF)) != 0) {
                flow += f;
            }
        }

        return flow;
    }

    static void findReached(Vertex v, List<Vertex> reachable) {
        v.mark = true;
        for (Rib rib : v.ribs) {
            if (!rib.end.mark && !rib.isSaturated()) {
                findReached(rib.end, reachable);
            }
        }
        reachable.add(v);
    }

    static void buildWalls() {
        List<Vertex> reachable = new ArrayList<>();
        findReached(SRC, reachable);
        for (Vertex v : reachable) {
            if (v.isSuitable()) {
                for (Rib rib : v.ribs) {
                    if (!rib.end.mark && rib.getFlow() == 1) {
                        v.buildWall();
                        break;
                    }
                }
            }
        }

    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        m = scanner.nextInt();
        n = scanner.nextInt();
        field = new ArrayList<>();
        scanner.nextLine();
        for (int i = 0; i < m; i++) {
            field.add(new ArrayList<>());
            String line = scanner.nextLine();
            for (int j = 0; j < n; j++) {
                field.get(i).add(new Cell(line.charAt(j)));
                if (i > 0) {
                    boundCells(field.get(i).get(j), field.get(i - 1).get(j));
                }
                if (j > 0) {
                    boundCells(field.get(i).get(j), field.get(i).get(j - 1));
                }
            }
        }

        long answ = maxFlowDinic();
        if (answ >= UNDEF) {
            System.out.println(-1);
        } else {
            buildWalls();
            System.out.println(answ);
            for (List<Cell> cells : field) {
                System.out.println(cells.stream().map(c -> String.valueOf(c.getName())).collect(Collectors.joining()));
            }
        }
    }
}
