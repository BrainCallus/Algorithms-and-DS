#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

const LL INF = 1000000000000000001;

struct Node {
    LL valC;
    LL valN;
    LL fSet;
};

vector<LL> arr;
vector<Node> tree;
int n;


void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        if (vl % 2 == 0) {
            tree[v].valC = arr[vl];
            tree[v].valN = -1 * arr[vl];
        } else {
            tree[v].valN = arr[vl];
            tree[v].valC = -1 * arr[vl];
        }

        tree[v].fSet = INF;
        return;
    }
    int vm = vl + (vr - vl) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    tree[v].valC = tree[2 * v + 1].valC + tree[2 * v + 2].valC;
    tree[v].valN = tree[2 * v + 1].valN + tree[2 * v + 2].valN;
    tree[v].fSet = INF;
}

void prop(int v, int vl, int vr) {
    if (tree[v].fSet == INF) {
        return;
    }
    if (vl % 2 == 0) {
        tree[v].valC = tree[v].fSet * (vr - vl);
        tree[v].valN = -1 * tree[v].fSet * (vr - vl);
    } else {
        tree[v].valN = tree[v].fSet * (vr - vl);
        tree[v].valC = -1 * tree[v].fSet * (vr - vl);
    }

    if (vr - vl > 1) {
        tree[2 * v + 1].fSet = tree[v].fSet;
        tree[2 * v + 2].fSet = tree[v].fSet;
    }
    tree[v].fSet = INF;

}

void modif(LL val, int ql, int qr, int v, int vl, int vr) {
    prop(v, vl, vr);
    if (qr <= vl || ql >= vr) {
        return;
    }
    if (ql <= vl && qr >= vr) {
        tree[v].fSet = val;
        return;
    }
    int vm = vl + (vr - vl) / 2;
    modif(val, ql, qr, 2 * v + 1, vl, vm);
    modif(val, ql, qr, 2 * v + 2, vm, vr);
    prop(2 * v + 1, vl, vm);
    prop(2 * v + 2, vm, vr);
    tree[v].valC = tree[2 * v + 1].valC + tree[2 * v + 2].valC;
    tree[v].valN = tree[2 * v + 1].valN + tree[2 * v + 2].valN;
}

LL getSum(int v, int ql, int qr, int vl, int vr) {
    prop(v, vl, vr);
    if (qr <= vl || ql >= vr) {
        return 0;
    } else if (ql <= vl && vr <= qr) {
        return ql % 2 == 0 ? tree[v].valC : tree[v].valN;
    }
    int vm = vl + (vr - vl) / 2;
    return getSum(2 * v + 1, ql, qr, vl, vm) + getSum(2 * v + 2, ql, qr, vm, vr);
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
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {

        int op, par1, par2;
        cin >> op >> par1 >> par2;
        if (op == 1) {
            cout << getSum(0, par1 - 1, par2, 0, n) << "\n";
        } else {
            modif(par2, par1 - 1, par1, 0, 0, n);
        }
    }
}