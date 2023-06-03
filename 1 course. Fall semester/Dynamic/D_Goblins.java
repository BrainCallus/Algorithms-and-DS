import java.util.Scanner;

public class D_Goblins {

    static class LinkedEl {
        private final int el;

        private LinkedEl prev;
        private LinkedEl next;

        public LinkedEl(int el, LinkedEl prev, LinkedEl next) {
            this.el = el;
            this.next = next;
            this.prev = prev;
        }
    }

    static class LList {
        private LinkedEl head;
        private LinkedEl tale;
        private LinkedEl middle;
        private int size;

        public LList() {
            tale = null;
            head = null;
            middle = null;
            size = 0;
        }

        public void addLast(int num) {
            LinkedEl el = new LinkedEl(num, null, null);
            if (tale == null) {
                head = el;
                tale = el;
                middle = el;
                el.prev = null;
            } else {
                tale.next = el;
                el.prev = tale;
                tale = el;
                if (size % 2 == 0) {
                    middle = middle.next;
                }
            }
            size++;
        }

        public void addMiddle(int num) {
            if (head == null) {
                addLast(num);
            } else {
                LinkedEl newMid = new LinkedEl(num, middle, middle.next);
                if (middle.next != null) {
                    middle.next.prev = newMid;
                } else {
                    tale = newMid;
                }
                middle.next = newMid;
                if (size % 2 == 0) {
                    middle = newMid;
                }
                size++;
            }

        }

        public int removeFirst() {
            if (head == null) {
                return 0;
            }
            int val = head.el;
            if (size == 1) {
                head = null;
                tale = null;
                middle = null;
            } else {
                head = head.next;
                head.prev = null;
                if (size % 2 == 0) {
                    middle = middle.next;
                }
            }
            size--;
            return val;
        }

    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        LList queue = new LList();
        for (int i = 0; i < n; i++) {
            switch (scanner.next()) {
                case "+" -> queue.addLast(scanner.nextInt());
                case "*" -> queue.addMiddle(scanner.nextInt());
                case "-" -> System.out.println(queue.removeFirst());
            }
        }
    }
}