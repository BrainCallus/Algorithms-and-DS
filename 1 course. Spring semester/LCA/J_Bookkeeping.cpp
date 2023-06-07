#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const LL MOD = 1000000007;
const LL NEUTRAL = 0;
int n, m;

struct Vertex {
    int num;
    int w = 1;
    LL salary = 0;
    int index = -1;
    int last = -1;
    vector<Vertex *> ribs;
    Vertex *heavy_path_root = this;
    Vertex *heavy = nullptr;
    Vertex *link = nullptr;

    explicit Vertex(int num) {
        this->num = num;
    }
};

vector<Vertex *> graph;
Vertex *pupa;
vector<LL> salaries;
vector<LL> pupa_salary;
int T;


void dfs(Vertex *v) {
    for (Vertex *u: v->ribs) {
        dfs(u);
        v->w += u->w;
        if (!v->heavy || u->w > v->heavy->w) {
            v->heavy = u;
        }
    }
}

void HLD(Vertex *v) {
    v->index = T++;
    v->link = v->heavy_path_root->link;
    salaries.push_back(v->salary);
    if (v->heavy) {
        v->heavy->heavy_path_root = v->heavy_path_root;
        HLD(v->heavy);
    }
    for (Vertex *u: v->ribs) {
        if (u != v->heavy) {
            u->link = v;
            HLD(u);
        }
    }
    v->last = T;
}

struct Node {
    LL sum = NEUTRAL;
    LL fAdd = NEUTRAL;
    int l;
    int r;
    Node *left;
    Node *right;

    explicit Node(int l, int r) {
        this->l = l;
        this->r = r;
        if (r - l > 1) {
            int mid = l + ((r - l) >> 1);
            left = new Node(l, mid);
            right = new Node(mid, r);
            sum = left->sum + right->sum;
        } else {
            sum = salaries[l];
        }
    }

    void propagate() {
        if (fAdd) {
            sum += fAdd * (r - l);
            if (r - l > 1) {
                left->fAdd += fAdd;
                right->fAdd += fAdd;
            }
            fAdd = NEUTRAL;
        }
    }
};

Node *tree;

void modify(Node *v, int ql, int qr, LL delta) {
    if (!v || v->l >= qr || v->r <= ql) {
        return;
    }
    if (v->l >= ql && v->r <= qr) {
        v->fAdd += delta;
        return;
    }
    v->propagate();
    modify(v->left, ql, qr, delta);
    modify(v->right, ql, qr, delta);
    if (v->left) {
        v->left->propagate();
    }
    if (v->right) {
        v->right->propagate();
    }
    v->sum = (v->left ? v->left->sum : 0) + (v->right ? v->right->sum : 0);
}

LL getSum(Node *v, int ql, int qr) {
    if (!v || v->l >= qr || v->r <= ql) {
        return NEUTRAL;
    }
    v->propagate();
    if (v->l >= ql && v->r <= qr) {
        return v->sum;
    }
    return getSum(v->left, ql, qr) + getSum(v->right, ql, qr);

}

void build() {
    dfs(graph[0]);
    T = 0;
    HLD(graph[0]);
    tree = new Node(0, n);
}

LL getSumToRoot(Vertex *v) {
    LL sum = 0;
    while (v) {
        sum += getSum(tree, v->heavy_path_root->index, v->index + 1);
        v = v->link;
    }
    return sum;
}

void modifyToRoot(Vertex *v, LL delta) {
    while (v) {
        modify(tree, v->heavy_path_root->index, v->index + 1, delta);
        v = v->link;
    }
}

LL getAddition(Vertex *a) {
    return (getSumToRoot(a) + getSum(tree, a->index + 1, a->last)) % MOD;
}

void increaseSalary(Vertex *b, LL delta) {
    modifyToRoot(b, delta);
    modify(tree, b->index + 1, b->last, delta);
}

LL getSingle(Vertex *worker) {
    return getSum(tree, worker->index, worker->index + 1);
}


int main() {
    cin >> n >> m;
    for (int i = 0; i ^ n; i++) {
        graph.push_back(new Vertex(i));
    }
    int p;
    for (int i = 1; i ^ n; i++) {
        cin >> p;
        graph[p]->ribs.push_back(graph[i]);
    }
    pupa = graph[n - 1];
    for (int i = 0; i ^ n; i++) {
        cin >> p;
        graph[i]->salary = p;
    }
    build();
    int a, b;
    pupa_salary.push_back(getSingle(pupa));
    for (int i = 0; i ^ m; i++) {
        cin >> a >> b;
        increaseSalary(graph[b], getAddition(graph[a]));
        pupa_salary.push_back(getSingle(pupa));
    }
    for (LL s: pupa_salary) {
        cout << s << " ";
    }
}
