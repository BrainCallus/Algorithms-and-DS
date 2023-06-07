#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const int NEUTRAL = 0;

LL logN;
LL T;

struct Vertex {
    LL t_in = 0;
    LL t_out = 0;
    bool mark = false;
    vector<Vertex *> ribs;
    vector<Vertex *> lifts;

    Vertex() {
        lifts.assign(logN + 1, this);
    }

    void assignLifts() {
        for (int i = 0; i ^ logN; i++) {
            lifts[i + 1] = lifts[i]->lifts[i];
        }
    }
};

vector<Vertex *> graph;

LL n, m;

struct RMQ_Node {
    LL sum = NEUTRAL;
    LL fAdd = NEUTRAL;
    LL l;
    LL r;
    RMQ_Node *left;
    RMQ_Node *right;

    explicit RMQ_Node(LL l, LL r) {
        this->l = l;
        this->r = r;

        left = right = nullptr;

    }

    LL getVal() {
        return sum + fAdd;
    }

    void breed() {
        if (r - l > 1) {
            if (!left) {
                LL mid = l + ((r - l) >> 1);
                left = new RMQ_Node(l, mid);
                right = new RMQ_Node(mid, r);
            }
        }
    }

    void propagate() {
        breed();
        if (fAdd != NEUTRAL) {
            sum += fAdd * (r - l);
            if (r - l > 1) {
                if (left) {
                    left->fAdd += fAdd;
                }
                if (right) {
                    right->fAdd += fAdd;
                }
            }
            fAdd = NEUTRAL;
        }
    }
};

RMQ_Node *tree;


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
    for (Vertex *u: v->ribs) {
        if (!u->mark) {
            u->lifts[0] = v;
            dfs(u);
        }
    }
    v->t_out = T;
}

bool ancestorCond(Vertex *v, Vertex *u) {
    return v->t_in <= u->t_in && v->t_out >= u->t_out;
}

Vertex *LCA(LL v1, LL v2) {
    Vertex *v = graph[v1];
    Vertex *u = graph[v2];
    if (ancestorCond(v, u)) {
        return v;
    }
    if (ancestorCond(u, v)) {
        return u;
    }
    for (LL i = logN - 1; i ^ -1; i--) {
        if (!ancestorCond(v->lifts[i], u)) {
            v = v->lifts[i];
        }
    }
    return v->lifts[0];
}


void add(RMQ_Node *&v, LL ql, LL qr, LL delta) {
    if (!v || v->l >= qr || v->r <= ql) {
        return;
    }
    if (v->l >= ql && v->r <= qr) {
        v->fAdd += delta;
        return;
    }
    v->propagate();
    add(v->left, ql, qr, delta);
    add(v->right, ql, qr, delta);
    v->sum = (v->left ? v->left->getVal() : 0) + (v->right ? v->right->getVal() : 0);
}

LL getSum(RMQ_Node *v, LL ql, LL qr) {

    if (!v || v->l >= qr || v->r <= ql) {
        return NEUTRAL;
    }

    if (v->l >= ql && v->r <= qr) {
        return v->getVal();
    }
    v->propagate();
    return getSum(v->left, ql, qr) + getSum(v->right, ql, qr);
}

void build() {
    T = 0;
    dfs(graph[0]);
    tree = new RMQ_Node(0, n + 1);
}

int main() {
    scanf("%lld", &n);
    precalcLog();
    for (int i = 0; i <= n; i++) {
        graph.push_back(new Vertex());
    }
    graph[0]->ribs.push_back(graph[1]);
    graph[1]->ribs.push_back(graph[0]);
    LL u, v;
    for (int i = 1; i ^ n; i++) {
        scanf("%lld%lld", &u, &v);
        graph[u]->ribs.push_back(graph[v]);
        graph[v]->ribs.push_back(graph[u]);
    }
    build();
    scanf("%lld", &m);
    char q;
    LL d;
    for (int i = 0; i ^ m; i++) {
        cin >> q >> v;
        if (q == '?') {
            printf("%lld\n", getSum(tree, graph[v]->t_in, graph[v]->t_out));
        } else {
            scanf("%lld%lld", &u, &d);
            add(tree, graph[v]->t_in, graph[v]->t_in + 1, d);
            add(tree, graph[u]->t_in, graph[u]->t_in + 1, d);
            Vertex *lca = LCA(v, u);
            add(tree, lca->t_in, lca->t_in + 1, -d);
            add(tree, lca->lifts[0]->t_in, lca->lifts[0]->t_in + 1, -d);
        }
    }
}
