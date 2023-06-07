#include <iostream>
#include<vector>
#include<random>

using namespace std;

const int INF = 2000000000;

int generateRand() {
    static mt19937 gen{random_device{}()};
    static uniform_int_distribution<int> distr(-10000, 10000);
    return distr(gen);
}


class Kurevo {
private:
    struct Node {
        int w;
        int val;
        int prior;
        Node *left;
        Node *right;

        Node() {
            w = 1;
            val = INF;
            prior = INF;
            right = left = nullptr;
        }

        explicit Node(int val) {
            w = 1;
            this->val = val;
            prior = generateRand();
            left = right = nullptr;
        }

        void refresh() {
            w = (left ? left->w : 0) + (right ? right->w : 0) + 1;
        }

        Node *findKMax(int k) {
            if (!this || k == (right ? right->w + 1 : 1)) {
                return this;
            }

            if (k <= (right ? right->w : 0)) {
                return right->findKMax(k);
            }
            return left->findKMax(k - (right ? right->w : 0) - 1);
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
        pair<Node *, Node *> sp = split(root, x);
        root = merge(merge(sp.first, new Node(x)), sp.second);
    }

    void remove(int x) {
        pair<Node *, Node *> res1 = split(root, x - 1);
        pair<Node *, Node *> res2 = split(res1.second, x);
        root = merge(res1.first, res2.second);
    }

    int KMax(int k) {
        return root->findKMax(k)->val;
    }

};


Kurevo *pupa;
int n;

int main() {
    pupa = new Kurevo();
    cin >> n;
    int query, arg;
    for (int i = 0; i ^ n; i++) {
        cin >> query >> arg;
        if (query == 1) {
            pupa->insert(arg);
        } else if (!query) {
            cout << pupa->KMax(arg) << "\n";
        } else {
            pupa->remove(arg);
        }
    }
}

