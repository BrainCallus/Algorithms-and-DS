#include <iostream>
#include <vector>

using namespace std;

const int INF = 2000000000;

struct Node {
    int val;
    int fSet;
};

vector<int> arr;
vector<Node> tree;
int n;


void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v].val = arr[vl];
        tree[v].fSet = INF;
        return;
    }
    build(2 * v + 1, vl, (vl + vr) / 2);
    build(2 * v + 2, (vl + vr) / 2, vr);
    tree[v].val = min(tree[2 * v + 1].val, tree[2 * v + 2].val);
    tree[v].fSet = INF;
}

void prop(int v, int vl, int vr) {
    if (tree[v].fSet == INF) {
        return;
    }
    tree[v].val = tree[v].fSet;
    if (vr - vl > 1) {
        tree[2 * v + 1].fSet = tree[v].fSet;
        tree[2 * v + 2].fSet = tree[v].fSet;
    }
    tree[v].fSet = INF;

}

void modif(int val, int ql, int qr, int v, int vl, int vr) {
    prop(v, vl, vr);
    if (qr <= vl || ql >= vr) {
        return;
    }
    if (ql <= vl && qr >= vr) {
        tree[v].fSet = val;
        return;
    }
    int vm = (vl + vr) / 2;
    modif(val, ql, qr, 2 * v + 1, vl, vm);
    modif(val, ql, qr, 2 * v + 2, vm, vr);
    prop(2 * v + 1, vl, vm);
    prop(2 * v + 2, vm, vr);
    tree[v].val = min(tree[2 * v + 1].val, tree[2 * v + 2].val);
}

int getMin(int v, int ql, int qr, int vl, int vr) {
    prop(v, vl, vr);
    if (qr <= vl || ql >= vr) {
        return INF;
    } else if (ql <= vl && vr <= qr) {
        return tree[v].val;
    }
    int vm = (vr + vl) / 2;
    return min(getMin(2 * v + 1, ql, qr, vl, vm), getMin(2 * v + 2, ql, qr, vm, vr));
}

int main() {
    cin >> n;
    int a;
    tree.resize(4 * n);
    for (int i = 0; i < n; i++) {
        cin >> a;
        arr.push_back(a);
    }
    build(0, 0, n);
    char *op = new char[3];
    while (scanf("%s", op) != EOF) {

        int par1, par2;
        cin >> par1 >> par2;
        if (op[0] == 'm') {
            cout << getMin(0, par1 - 1, par2, 0, n) << "\n";
        } else {
            modif(par2, par1 - 1, par1, 0, 0, n);
        }
    }
}