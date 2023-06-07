#include <iostream>
#include<vector>

using namespace std;

const int INF = INT32_MAX;
int logN;


int min(int a, int b) {
    return a < b ? a : b;
}

struct Vertex {
    int numb;
    bool mark;
    int t_in;
    int t_out;
    vector<pair<Vertex *, int>> children;
    vector<pair<Vertex *, int>> lifts;

    explicit Vertex(int numb) {
        this->numb = numb;
        mark = false;
        t_in = t_out = 0;
        lifts.assign(logN + 1, {this, INF});
    }

    void assignLifts() {
        for (int i = 0; i ^ logN; i++) {
            lifts[i + 1].first = lifts[i].first->lifts[i].first;
            lifts[i + 1].second = min(lifts[i].second, lifts[i].first->lifts[i].second);
        }
    }

};

vector<Vertex *> graph;
vector<int> logs;

Vertex *pupa;

int n, m;
int T;

void precalcLog() {
    logN = 1;
    while ((1 << logN) <= n) {
        logN++;
    }
}

void dfs(Vertex *v) {
    v->mark = true;
    v->t_in = T++;
    v->assignLifts();
    for (pair<Vertex *, int> child: v->children) {
        if (!child.first->mark) {
            child.first->lifts[0] = {v, child.second};
            dfs(child.first);
        }
    }
    v->t_out = T++;
}

bool ancestorCond(Vertex *v, Vertex *u) {
    return v->t_in <= u->t_in && v->t_out >= u->t_out;
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
        if (!ancestorCond(v->lifts[i].first, u)) {
            v = v->lifts[i].first;
        }
    }
    return v->lifts[0].first;
}

int getMin(int v1, int v2) {
    if (v1 == v2) {
        return 0;
    }
    int minn = INF;
    Vertex *v = graph[v1], *u = graph[v2];
    for (int i = logN; i >= 0; i--) {
        if (!ancestorCond(v->lifts[i].first, u)) {
            minn = min(minn, v->lifts[i].second);
            v = v->lifts[i].first;
        }
    }
    if (!ancestorCond(v, u)) {
        minn = min(minn, v->lifts[0].second);
    }
    for (int i = logN; i >= 0; i--) {
        if (!ancestorCond(u->lifts[i].first, v)) {
            minn = min(minn, u->lifts[i].second);
            u = u->lifts[i].first;
        }
    }
    if (!ancestorCond(u, v)) {
        minn = min(minn, u->lifts[0].second);
    }
    return minn;
}

void build() {
    T = 0;
    dfs(graph[1]);
}

int main() {
    cin >> n;
    precalcLog();
    graph.push_back(new Vertex(0));
    for (int i = 1; i <= n; i++) {
        graph.push_back(new Vertex(i));
    }
    pupa = graph[0];
    pupa->children.emplace_back(graph[1], INF);
    int x, cost;
    for (int i = 2; i <= n; i++) {
        cin >> x >> cost;
        graph[x]->children.emplace_back(graph[i], cost);
    }
    build();
    cin >> m;
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cout << getMin(u, v) << "\n";
    }
}
