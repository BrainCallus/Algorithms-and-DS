#include<iostream>
#include<set>
#include<map>
#include<vector>

using namespace std;


vector<vector<int>> bonds;
vector<bool> mark;
map<pair<int, int>, int> ribs;
set<int> bridges;
vector<int> tin;
vector<int> up;
static int T = 0;

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
            if (tin[v] < up[u]) {
                bridges.insert(ribs[keyRib(v, u)]);
            }
        }
    }

}


void serchBridge() {
    T = 0;
    for (int i = 1; i < bonds.size(); i++) {
        if (!mark[i]) {
            dfs(i, -1);
        }
    }
}


int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    bonds.resize(n + 1);
    mark.resize(n + 1);
    tin.resize(n + 1);
    up.resize(n + 1);

    for (int i = 1; i <= m; i++) {
        int versh, child;
        cin >> versh >> child;
        bonds[versh].push_back(child);
        bonds[child].push_back(versh);
        ribs[keyRib(child, versh)] = i;
    }

    serchBridge();
    cout << bridges.size() << "\n";


    if (!bridges.empty()) {
        for (int bridge: bridges) {
            cout << bridge << " ";
        }
    }
    return 0;
}
