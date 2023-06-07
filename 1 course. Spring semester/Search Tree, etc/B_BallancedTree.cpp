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

struct Node {

    int val = INF;
    int prior = INF;
    Node *left = nullptr;
    Node *right = nullptr;

    Node() = default;

    explicit Node(int val) {
        this->val = val;
        prior = generateRand();
        left = right = nullptr;
    }

};

Node *merge(Node *, Node *);

pair<Node *, Node *> split(Node *, int);

Node *next(Node *v, int x) {
    if (!v) {
        return nullptr;
    }
    if (v->val == x) {
        return v;
    }
    if (x < v->val) {
        Node *res = next(v->left, x);
        return res ? res : v;
    }
    return next(v->right, x);
}

Node *prev(Node *v, int x) {
    if (!v) {
        return nullptr;
    }
    if (v->val == x) {
        return v;
    }
    if (x > v->val) {
        Node *res = prev(v->right, x);
        return res ? res : v;
    }
    return prev(v->left, x);
}

Node *find(Node *v, int x) {
    if (!v) {
        return nullptr;
    }
    if (v->val == x) {
        return v;
    }
    if (x < v->val) {
        return find(v->left, x);
    }
    return find(v->right, x);
}

Node *insert(Node *v, int x) {
    if (find(v, x)) {
        return v;
    }
    Node *newX = new Node(x);
    pair<Node *, Node *> sp = split(v, x);
    return merge(merge(sp.first, newX), sp.second);
}

Node *remove(Node *v, int x) {
    Node *res = find(v, x);
    if (!res) {
        return v;
    }
    pair<Node *, Node *> res1 = split(v, x - 1);
    pair<Node *, Node *> res2 = split(res1.second, x);
    return merge(res1.first, res2.second);
}

pair<Node *, Node *> split(Node *v, int x) {
    if (!v) {
        return {nullptr, nullptr};
    }
    if (v->val <= x) {
        pair<Node *, Node *> res = split(v->right, x);
        v->right = res.first;
        return {v, res.second};
    }
    pair<Node *, Node *> res = split(v->left, x);
    v->left = res.second;
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
        return v1;
    }
    v2->left = merge(v1, v2->left);
    return v2;
}

Node *pupa;

int main() {
    pupa = new Node();
    string query;
    int val;
    while (cin >> query) {
        cin >> val;
        switch (query[0]) {
            case 'i': {
                pupa = insert(pupa, val);
                break;
            }
            case 'd': {
                pupa = remove(pupa, val);
                break;
            }
            case 'e': {
                if (find(pupa, val)) {
                    cout << "true\n";
                } else {
                    cout << "false\n";
                }
                break;
            }
            case 'n': {
                Node *res = next(pupa, ++val);
                if (!res || res->val == INF) {
                    cout << "none\n";
                } else {
                    cout << res->val << "\n";
                }
                break;
            }
            case 'p': {
                Node *res = prev(pupa, --val);
                if (!res) {
                    cout << "none\n";
                } else {
                    cout << res->val << "\n";
                }
                break;
            }
            default:
                break;
        }
    }
}

