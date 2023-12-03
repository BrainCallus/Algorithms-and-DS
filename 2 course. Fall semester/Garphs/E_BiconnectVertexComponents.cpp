#include<iostream>
#include<vector>
#include<map>

using namespace std;

vector<vector<int>> bonds;
vector<bool> mark;
map<pair<int, int>, vector<int>> ribs;
vector<int> tin;
vector<int> up;
vector<int> comp;
static int T = 0;
static int numComp;

pair<int, int> keyRib(int v, int u) {
    if (v > u) {
        int tmp = v;
        v = u;
        u = tmp;
    }

    return make_pair(v, u);
}

vector<bool> fillFalse(vector<bool> f) {
    for (auto &&i: f) {
        i = false;
    }
    return f;
}


void addToComp(int v, int u, int num) {
    vector<int> rib = ribs[keyRib(v, u)];
    for (int i: rib) {
        comp[i] = num;
    }
}

void dfs1(int v, int p) {
    tin[v] = T++;
    up[v] = tin[v];
    mark[v] = true;
    for (int i = 0; i < bonds[v].size(); ++i) {
        int u = bonds[v][i];
        if (u == p) {
            continue;
        }
        if (mark[u]) {
            up[v] = min(up[v], tin[u]);
        } else {
            dfs1(u, v);
            up[v] = min(up[v], up[u]);
        }
    }
}

void dfs2(int v, int p, int ncomp) {
    mark[v] = true;
    for (int i = 0; i < bonds[v].size(); ++i) {
        int u = bonds[v][i];
        if (u == p) continue;
        if (mark[u]) {
            if (tin[u] < tin[v]) {
                addToComp(v, u, ncomp);
            }
        } else {
            if (up[u] >= tin[v]) {
                numComp++;
                int num = numComp;
                addToComp(v, u, num);
                dfs2(u, v, num);
            } else {
                addToComp(v, u, ncomp);
                dfs2(u, v, ncomp);
            }
        }
    }
}

void serchBridge() {
    T = 0;
    numComp = 0;
    for (int i = 1; i < bonds.size(); ++i) {
        if (!mark[i]) {
            dfs1(i, -1);
        }
    }

    mark.assign(bonds.size(), false);
    for (int i = 1; i < bonds.size(); ++i) {
        if (!mark[i]) {
            dfs2(i, -1, numComp);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    bonds.resize(n + 1);
    mark.assign(n + 1, false);
    tin.resize(n + 1);
    up.resize(n + 1);
    comp.resize(m + 1);

    for (int i = 1; i <= m; i++) {
        int versh = 0, child = 0;
        cin >> versh >> child;
        bonds[versh].push_back(child);
        bonds[child].push_back(versh);
        ribs[keyRib(child, versh)].push_back(i);
    }
    serchBridge();
    cout << numComp << "\n";
    for (int i = 1; i < comp.size(); i++) {
        cout << comp[i] << " ";
    }
}
