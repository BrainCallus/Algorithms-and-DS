#include <iostream>
#include<vector>
#include <unordered_map>

using namespace std;

int logN;

struct Vertex {
    int num;
    int t_in = 0;
    int t_out = 0;
    int self_color = 0;
    int unique_colors = 1;
    vector<Vertex *> lifts;
    vector<Vertex *> children;

    explicit Vertex(int num) {
        this->num = num;
        lifts.assign(logN + 1, this);
    }
};

vector<Vertex *> graph;
unordered_map<int, int> color_lastPos;
Vertex *pupa;

int n;
int T;

void precalcLog() {
    logN = 1;
    while ((1 << logN) <= n) {
        logN++;
    }
}


void dfs(Vertex *v) {
    v->t_in = T++;
    for (int i = 1; i <= logN; i++) {
        v->lifts[i] = v->lifts[i - 1]->lifts[i - 1];
    }
    for (Vertex *u: v->children) {
        u->lifts[0] = v;
        dfs(u);
    }
    v->t_out = T;
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
    for (int i = logN - 1; i ^ -1; i--) {
        if (!ancestorCond(v->lifts[i], u)) {
            v = v->lifts[i];
        }
    }
    return v->lifts[0];
}

void colorDFS(Vertex *&v) {
    for (Vertex *u: v->children) {
        colorDFS(u);
        v->unique_colors += u->unique_colors;
    }
    if (color_lastPos[v->self_color] != -1) {
        LCA(v->num, color_lastPos[v->self_color])->unique_colors--;
    }
    color_lastPos[v->self_color] = v->num;
}

void build() {
    T = 0;
    dfs(pupa);
}

void computeColors() {
    colorDFS(pupa);
    for (int i = 1; i <= n; i++) {
        cout << graph[i]->unique_colors << " ";
    }
}

int main() {
    cin >> n;
    precalcLog();
    for (int i = 0; i <= n; i++) {
        graph.push_back(new Vertex(i));
    }
    int p, c;
    for (int i = 1; i <= n; i++) {
        cin >> p >> c;
        if (!p) {
            pupa = graph[i];
        } else {
            graph[p]->children.push_back(graph[i]);
        }
        graph[i]->self_color = c;
        color_lastPos[c] = -1;
    }
    build();
    computeColors();
}
