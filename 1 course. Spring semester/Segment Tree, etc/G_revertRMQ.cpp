#include <iostream>
#include <vector>

using namespace std;

const int NEUTRAL = INT32_MAX;

vector<int> arr;

struct Node {
    int minn;
    int fSet = NEUTRAL;
    int l;
    int r;
    Node *left = nullptr;
    Node *right = nullptr;

    explicit Node(int l, int r) {
        this->l = l;
        this->r = r;
        if (r - l > 1) {
            int mid = l + (r - l) / 2;
            left = new Node(l, mid);
            right = new Node(mid, r);
        }
        minn = INT32_MIN;
    }

    void propagate() {
        if (left) {
            left->minn = max(minn, left->minn);
            right->minn = max(minn, right->minn);
            minn = min(left->minn, right->minn);
        }
    }

};

struct Query {
    int l;
    int r;
    int val;

    explicit Query(int l, int r, int val) {
        this->l = l;
        this->r = r;
        this->val = val;
    }
};

Node *root;

vector<Query *> queries;
int n, m;


void modify(Node *v, int ql, int qr, int val) {

    if (!v || v->l >= qr || v->r <= ql) {
        return;
    }
    if (v->l >= ql && v->r <= qr) {
        v->minn = max(v->minn, val);
        return;
    }
    v->propagate();
    modify(v->left, ql, qr, val);
    modify(v->right, ql, qr, val);
    v->minn = min(v->left->minn, v->right->minn);

}

int getVal(Node *v, int ql, int qr) {
    if (!v || v->l >= qr || v->r <= ql) {
        return NEUTRAL;
    }
    if (v->l >= ql && v->r <= qr) {
        return v->minn;
    }
    return min(getVal(v->left, ql, qr), getVal(v->right, ql, qr));
}

void mass_propagation(Node *v) {
    if (v->left) {
        v->propagate();
        mass_propagation(v->left);
        mass_propagation(v->right);
    } else {
        arr[v->l] = v->minn;
    }
}

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    cin >> n >> m;
    root = new Node(0, n);
    int ql, qr, qVal;

    for (int i = 0; i ^ m; i++) {
        cin >> ql >> qr >> qVal;
        --ql;
        queries.push_back(new Query(ql, qr, qVal));
        modify(root, ql, qr, qVal);
    }
    arr.resize(n);
    mass_propagation(root);
    for (Query *query: queries) {
        if (query->val != getVal(root, query->l, query->r)) {
            cout << "inconsistent";
            return 0;
        }
    }
    cout << "consistent\n";
    for (int a: arr) {
        cout << a << " ";
    }
}