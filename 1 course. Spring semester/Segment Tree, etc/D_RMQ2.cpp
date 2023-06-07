#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

const LL MIN_NEUTRAL = 2000000000000000000;
const LL ADD_NEUTRAL = 0;

struct Node {
    LL val;
    LL fSet;
    LL fAdd;

};

vector<LL> arr;
vector<Node> tree;
int n;


void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v].val = arr[vl];
        tree[v].fSet = MIN_NEUTRAL;
        return;
    }
    int vm = vl + (vr - vl) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    tree[v].val = min(tree[2 * v + 1].val, tree[2 * v + 2].val);
    tree[v].fSet = MIN_NEUTRAL;
    tree[v].fAdd = ADD_NEUTRAL;
}

void prop(int v, int vl, int vr) {
    if (tree[v].fSet != MIN_NEUTRAL) {
        tree[v].val = tree[v].fSet;
        if (vr - vl > 1) {
            tree[2 * v + 1].fSet = tree[v].fSet;
            tree[2 * v + 2].fSet = tree[v].fSet;
            tree[2 * v + 1].fAdd = ADD_NEUTRAL;
            tree[2 * v + 2].fAdd = ADD_NEUTRAL;
        }
        tree[v].fSet = MIN_NEUTRAL;
    } else if (tree[v].fAdd != ADD_NEUTRAL) {
        tree[v].val += tree[v].fAdd;
        if (vr - vl > 1) {
            if (tree[2 * v + 1].fSet != MIN_NEUTRAL)
                prop(2 * v + 1, vl, vl + (vr - vl) / 2);
            tree[2 * v + 1].fAdd += tree[v].fAdd;
            if (tree[2 * v + 2].fSet != MIN_NEUTRAL)
                prop(2 * v + 2, vl + (vr - vl) / 2, vr);
            tree[2 * v + 2].fAdd += tree[v].fAdd;
        }
        tree[v].fAdd = ADD_NEUTRAL;
    }

}

void modif(LL val, int ql, int qr, int v, int vl, int vr, char mode) {
    prop(v, vl, vr);
    if (qr <= vl || ql >= vr) {
        return;
    }

    if (ql <= vl && qr >= vr) {
        (mode == 's') ? tree[v].fSet = val : tree[v].fAdd += val;
        return;
    }

    int vm = vl + (vr - vl) / 2;
    modif(val, ql, qr, 2 * v + 1, vl, vm, mode);
    modif(val, ql, qr, 2 * v + 2, vm, vr, mode);
    prop(2 * v + 1, vl, vm);
    prop(2 * v + 2, vm, vr);
    tree[v].val = min(tree[2 * v + 1].val, tree[2 * v + 2].val);
}

LL getMin(int v, int ql, int qr, int vl, int vr) {
    prop(v, vl, vr);
    if (qr <= vl || ql >= vr) {
        return MIN_NEUTRAL;
    } else if (ql <= vl && vr <= qr) {
        return tree[v].val;
    }
    int vm = vl + (vr - vl) / 2;
    return min(getMin(2 * v + 1, ql, qr, vl, vm), getMin(2 * v + 2, ql, qr, vm, vr));
}

int main() {
    cin >> n;
    LL a;
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
            int val;
            cin >> val;
            modif(val, par1 - 1, par2, 0, 0, n, op[0]);
        }
    }
}