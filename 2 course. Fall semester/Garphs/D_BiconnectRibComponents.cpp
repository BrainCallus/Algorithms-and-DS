#include<iostream>
#include<vector>
#include<map>
#include<set>

using namespace std;


vector<vector<int>> bonds;
vector<bool> mark, mr;
vector<int> stack;
map<pair<int, int>, int> ribs;
vector<int> tin;
vector<int> up;
vector<int> comp;
set<int> bridges;
static int T = 0;
static int numComp;;

vector<bool> fillFalse(vector<bool> f) {
    for (auto &&i: f) {
        i = false;
    }
    return f;
}

pair<int, int> keyRib(int v, int u) {
    if (v > u) {
        int tmp = v;
        v = u;
        u = tmp;
    }

    return make_pair(v, u);
}

void dfs(int v, int p) {
    tin[v] = T++;
    up[v] = tin[v];
    mark[v] = true;
    stack.push_back(v);
    for (int i = 0; i < bonds[v].size(); i++) {
        int u = (int) bonds[v][i];
        if (u == p) {
            continue;
        }
        if (mark[u]) {
            up[v] = min(up[v], tin[u]);
        } else {
            dfs(u, v);
            up[v] = min(up[v], up[u]);
            if (tin[v] < up[u] && !mr[ribs[keyRib(v, u)]]) {
                bridges.insert(ribs[keyRib(v, u)]);
            }
        }
    }
}

void dfs2(int v, int num) {
    comp[v] = num;
    for (int i = 0; i < bonds[v].size(); ++i) {
        int u = bonds[v][i];
        if (comp[u] == 0) {
            if (bridges.find(ribs[keyRib(v, u)]) == bridges.end()) {
                dfs2(u, num);
            } else {
                numComp++;
                dfs2(u, numComp);
            }
        }
    }
}

void serchBridge() {
    T = 0;
    numComp = 0;
    for (int i = 1; i < bonds.size(); i++) {
        if (!mark[i]) {
            dfs(i, -1);
        }
    }
    for (int i = 1; i < bonds.size(); i++) {
        if (comp[i] == 0) {
            numComp++;
            dfs2(i, numComp);
        }
    }

}

int main() {
    int n, m;
    cin >> n >> m;

    bonds.resize(n + 1);
    mark.resize(n + 1);
    mr.resize(m + 1);
    mark = fillFalse(mark);
    mr = fillFalse(mr);
    tin.resize(n + 1);
    up.resize(n + 1);
    comp.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int versh = 0, child = 0;
        cin >> versh >> child;
        bonds[versh].push_back(child);
        bonds[child].push_back(versh);
        if (ribs[keyRib(versh, child)] == 0) {
            ribs[keyRib(versh, child)] = i;
        } else {
            mr[ribs[keyRib(versh, child)]] = true;
        }
    }


    serchBridge();
    cout << numComp << "\n";

    for (int i = 1; i < comp.size(); i++) {
        cout << comp[i] << " ";
    }
}

