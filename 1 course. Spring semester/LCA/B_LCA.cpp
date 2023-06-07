#include <iostream>
#include<vector>

using namespace std;

int logN;

struct Vertex {
    int numb;
    bool mark;
    int t_in;
    int t_out;
    vector<Vertex *> children;
    vector<Vertex *> lifts;

    explicit Vertex(int numb) {
        this->numb = numb;
        mark = false;
        t_in = t_out = 0;
        lifts.assign(logN, this);
    }
};

vector<Vertex *> graph;
vector<int> logs;

Vertex *pupa;
int T;

void precalcLog(int n) {
    logs.resize(n);
    logs[0] = -1;
    for (int i = 1; i < n; i++) {
        logs[i] = logs[i / 2] + 1;
    }
    logN = logs[n - 1];
}

void dfs(Vertex *v) {
    v->mark = true;
    v->t_in = T++;
    for (int i = 1; i < logN; i++) {
        v->lifts[i] = v->lifts[i - 1]->lifts[i - 1];
    }
    for (Vertex *child: v->children) {
        if (!child->mark) {
            child->lifts[0] = v;
            dfs(child);
        }
    }
    v->t_out = T++;
}

bool ancestorCond(Vertex *v, Vertex *u) {
    return v->t_in < u->t_in && v->t_out > u->t_out;
}

Vertex *LCA(int v1, int v2) {
    Vertex *v = graph[v1];
    Vertex *u = graph[v2];
    if (ancestorCond(v, u)) {
        return v;
    }
    if (ancestorCond(u, v)) {
        return u;
    }
    for (int i = logN - 1; i >= 0; i--) {
        if (!ancestorCond(v->lifts[i], u)) {
            v = v->lifts[i];
        }
    }
    return v->lifts[0];
}

void build() {
    T = 0;
    dfs(pupa);
}

int main() {
    int n, m;
    cin >> n;
    precalcLog(n + 1);
    graph.push_back(new Vertex(0));
    for (int i = 1; i <= n; i++) {
        graph.push_back(new Vertex(i));
    }
    pupa = graph[0];
    pupa->children.push_back(graph[1]);
    int x;
    for (int i = 2; i <= n; i++) {
        cin >> x;
        graph[x]->children.push_back(graph[i]);
    }
    build();
    cin >> m;
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cout << LCA(u, v)->numb << "\n";
    }
}
