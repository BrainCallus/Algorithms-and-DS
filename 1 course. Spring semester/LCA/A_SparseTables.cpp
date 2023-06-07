#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

vector<vector<LL>> sparse;
vector<LL> layer;

void initAll(int &sz, int &a0) {
    layer.resize(sz + 1);
    layer[0] = -1;
    for (int i = 1; i <= sz; i++) {
        layer[i] = layer[i / 2] + 1;
    }

    vector<LL> zero(sz);
    zero[0] = a0;
    for (int i = 1; i < sz; i++) {
        zero[i] = (zero[i - 1] * 23 + 21563) % 16714589;
    }
    sparse.push_back(zero);

    for (int i = 0; (1 << i) < sz; i++) {
        int a = (1 << i);
        int b = sparse[i].size();
        if (a > b) {
            break;
        }
        vector<LL> nlay;
        for (int j = 0; j < sparse[i].size() - (1 << i); j++) {
            nlay.push_back(min(sparse[i][j], sparse[i][j + (1 << (i))]));
        }
        sparse.push_back(nlay);
    }
}

LL getMin(int ql, int qr) {
    if (qr - ql == 0) {
        return sparse[0][ql];
    }
    return min(sparse[layer[qr - ql + 1]][ql], sparse[layer[qr - ql + 1]][qr - (1 << (layer[qr - ql + 1])) + 1]);

}

int main() {
    int n, m, a0, u, v;
    cin >> n >> m >> a0 >> u >> v;
    initAll(n, a0);
    int r = getMin(min(u, v) - 1, max(u, v) - 1);
    for (int i = 1; i < m; i++) {
        u = ((u * 17 + 751 + r + 2 * i) % n) + 1;
        v = ((v * 13 + 593 + r + 5 * i) % n) + 1;
        r = getMin(min(u, v) - 1, max(u, v) - 1);
    }
    cout << u << " " << v << " " << r;
}


