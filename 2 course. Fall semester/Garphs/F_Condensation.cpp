#include<iostream>
#include<set>
#include<vector>

using namespace std;

vector<vector<int>> bonds;
vector<vector<int>> bondsAnti;
vector<bool> mark;
vector<int> comp;
vector<int> tout;
int T = 0;
set<pair<int, int>> bridges;


static void frstdfs(int v) {
    mark[v] = true;
    T++;
    for (int i: bonds[v]) {
        int u = (int) i;
        if (!mark[u]) {
            frstdfs(u);
        }
    }
    tout.push_back(v);
}

static void scnddfs(int v, int cmp) {
    mark[v] = true;
    comp[v] = cmp;
    for (int i: bondsAnti[v]) {
        int u = (int) i;
        if (!mark[u]) {
            scnddfs(u, cmp);
        }
    }
}

static void count() {
    for (int i = 1; i < bonds.size(); i++) {
        for (int j = 0; j < bonds[i].size(); j++) {
            int u = (int) bonds[i][j];
            if (comp[u] != comp[i]) {
                bridges.insert(make_pair(comp[u], comp[i]));
            }
        }
    }
}

static void countRibs() {
    T = 1;
    for (int i = 1; i < bonds.size(); i++) {
        if (!mark[i]) {
            frstdfs(i);
        }
    }
    int cmp = 1;
    mark.assign(bondsAnti.size(), false);
    for (int i = tout.size() - 1; i >= 0; i--) {
        if (!mark[tout[i]]) {
            scnddfs(tout[i], cmp);
            cmp++;
        }
    }
    count();
    cout << bridges.size();
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    bonds.resize(n + 1);
    bondsAnti.resize(n + 1);
    mark.assign(n + 1, false);
    comp.resize(bonds.size());

    for (int i = 0; i < m; i++) {
        int versh, child;
        cin >> versh >> child;
        bonds[versh].push_back(child);
        bondsAnti[child].push_back(versh);
    }
    countRibs();
}
