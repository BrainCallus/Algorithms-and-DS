#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *stack = new int[n];
    int ptr = -1;
    int oper;
    int el;
    for (int i = 0; i < n; i++) {
        scanf("%d", &oper);
        switch (oper) {
            case 1 : {
                scanf("%d", &el);
                ++ptr;
                stack[ptr] = ptr == 0 ? el : min(stack[ptr - 1], el);
                break;
            }
            case 2: {
                ptr--;
                break;
            }
            case 3 : {
                printf("%d\n", stack[ptr]);
            }
        }
    }
}
