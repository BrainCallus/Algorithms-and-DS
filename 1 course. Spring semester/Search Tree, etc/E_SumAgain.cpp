#include <iostream>
#include<vector>
#include<random>

using namespace std;
typedef long long LL;

const LL INF = 2000000000;
const LL MOD = 1000000000;

int generateRand() {
    static mt19937 gen{random_device{}()};
    static uniform_int_distribution<int> distr(-10000, 10000);
    return distr(gen);
}


class Kurevo {
private:
    struct Node {
        int val, prior, minn, maxx, w;
        LL common_data;
        Node *left;
        Node *right;

        Node() {
            w = 1;
            val = prior = INF;
            minn = maxx = common_data = val;
            right = left = nullptr;
        }

        explicit Node(int val) {
            w = 1;
            this->val = val;
            minn = maxx = common_data = val;
            prior = generateRand();
            left = right = nullptr;
        }

        void refresh() {
            w = (left ? left->w : 0) + (right ? right->w : 0) + 1;
            common_data = val + (left ? left->common_data : 0) + (right ? right->common_data : 0);
            minn = left ? left->minn : val;
            maxx = right ? right->maxx : val;
        }

    };

    Node *root;

    pair<Node *, Node *> split(Node *v, int x) {
        if (!v) {
            return {nullptr, nullptr};
        }
        if (v->val <= x) {
            pair<Node *, Node *> res = split(v->right, x);
            v->right = res.first;
            v->refresh();
            return {v, res.second};
        }
        pair<Node *, Node *> res = split(v->left, x);
        v->left = res.second;
        v->refresh();
        return {res.first, v};
    }

    Node *merge(Node *v1, Node *v2) {
        if (!v2) {
            return v1;
        }
        if (!v1) {
            return v2;
        }
        if (v1->prior > v2->prior) {
            v1->right = merge(v1->right, v2);
            v1->refresh();
            return v1;
        }
        v2->left = merge(v1, v2->left);
        v2->refresh();
        return v2;
    }

public:
    Kurevo() {
        root = nullptr;
    }

    ~Kurevo() {
        delete root;
    }

    void insert(int x) {
        if (!root) {
            root = new Node(x);
            return;
        }
        pair<Node *, Node *> res1 = split(root, x - 1);
        pair<Node *, Node *> res2 = split(res1.second, x);
        root = merge(merge(res1.first, new Node(x)), res2.second);
    }

    LL getSum(Node *v, int ql, int qr) {
        if (!v || ql > v->maxx || qr < v->minn) {
            return 0;
        }
        if (ql <= v->minn && qr >= v->maxx) {
            return v->common_data;
        }
        return getSum(v->left, ql, qr) + getSum(v->right, ql, qr) + ((v->val >= ql && v->val <= qr) ? v->val : 0);

    }

    LL getSum(int ql, int qr) {
        return getSum(root, ql, qr);
    }

};

Kurevo *treap;
int n;

int main() {
    treap = new Kurevo();
    cin >> n;
    char query;
    LL res = -1;
    for (int i = 0; i ^ n; i++) {
        cin >> query;
        if (query == '+') {
            int val;
            cin >> val;
            if (res + 1) {
                treap->insert((res + val) % MOD);
            } else {
                treap->insert(val);
            }
            res = -1;
        } else {
            int l, r;
            cin >> l >> r;
            res = treap->getSum(l, r);
            cout << res << "\n";
        }
    }
}

