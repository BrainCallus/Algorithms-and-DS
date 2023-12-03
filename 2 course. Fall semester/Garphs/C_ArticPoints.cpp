#include<iostream>
#include<vector>
#include<set>

using namespace std;

vector<vector<int>> bonds;
vector<bool> mark;
set<int> points;
vector<int> tin;
vector<int> up;
int T = 0;
int n, m;

void dfs(int v, int p) {
    tin[v] = T++;
    up[v] = tin[v];
    mark[v] = true;
    int ch = 0;
    for (int i = 0; i < bonds[v].size(); i++) {
        int u = bonds[v][i];
        if (u != p) {
            if (mark[u]) {
                up[v] = min(up[v], tin[u]);
            } else {
                dfs(u, v);
                ch++;
                up[v] = min(up[v], up[u]);

                if (tin[v] <= up[u] && p != -1) {
                    points.insert(v);
                }
            }
        }
    }
    if (p == -1 && ch > 1) points.insert(v);
}

static void serchPoint() {
    T = 0;
    for (int i = 1; i <= n; ++i) {
        if (!mark[i]) {
            dfs(i, -1);
        }
    }
}

void fillFalse(vector<bool>);

int main() {
    cin >> n >> m;
    bonds.resize(n + 1);
    mark.resize(n + 1);
    fillFalse(mark);
    tin.resize(n + 1, 0);
    up.resize(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int versh = 0, child = 0;
        cin >> versh >> child;
        bonds[versh].push_back(child);
        bonds[child].push_back(versh);
    }

    serchPoint();
    cout << points.size() << "\n";
    if (!points.empty()) {
        for (int point: points) {
            cout << point << " ";
        }
    }

}

void fillFalse(vector<bool> f) {
    for (auto &&i: f) {
        i = false;
    }
}