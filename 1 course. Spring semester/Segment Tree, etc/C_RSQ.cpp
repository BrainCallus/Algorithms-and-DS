#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

const LL INF = 1000000000000000001;

struct Node {
    LL val;
    LL fSet;
};

vector<LL> arr;
vector<Node> tree;
int n;


void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v].val = arr[vl];
        tree[v].fSet = INF;
        return;
    }
    int vm = vl + (vr - vl) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    tree[v].val = tree[2 * v + 1].val + tree[2 * v + 2].val;
    tree[v].fSet = INF;
}

void prop(int v, int vl, int vr) {
    if (tree[v].fSet == INF) {
        return;
    }
    tree[v].val = tree[v].fSet * (vr - vl); //len==1 => +f*1
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
    tree[v].val = tree[2 * v + 1].val + tree[2 * v + 2].val;
}

LL getSum(int v, int ql, int qr, int vl, int vr) {
    prop(v, vl, vr);
    if (qr <= vl || ql >= vr) {
        return 0;
    } else if (ql <= vl && vr <= qr) {
        return tree[v].val;
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
    char *op = new char[3];
    while (scanf("%s", op) != EOF) {

        int par1, par2;
        cin >> par1 >> par2;
        if (op[1] == 'u') {
            cout << getSum(0, par1 - 1, par2, 0, n) << "\n";
        } else {
            modif(par2, par1 - 1, par1, 0, 0, n);
        }
    }
}