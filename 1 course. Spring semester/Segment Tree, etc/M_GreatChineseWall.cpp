#include <iostream>

#define NEUTRAL 100000000
using namespace std;

template<typename NumType>
class SegmentTree {
private:
    struct Node {
        NumType val;
        int index;
        NumType fSet = NEUTRAL;
        int l, r;
        Node *left;
        Node *right;

        explicit Node(int l, int r) {
            this->l = l;
            this->r = r;
            if (r - l > 1) {
                int mid = l + ((r - l) >> 1);
                left = new Node(l, mid);
                right = new Node(mid, r);
            }
            val = 0;
            index = l;
        }

        void propagate() {
            if (fSet != NEUTRAL) {
                if (fSet < val) {
                    return;
                }
                val = fSet;
                if (r - l > 1) {
                    left->fSet = fSet;
                    right->fSet = fSet;
                }
                fSet = NEUTRAL;
            }
        }
    };

    Node *root;


    NumType (*oper)(NumType &, NumType &);

    NumType getVal(Node *v) {
        return v ? v->val : NEUTRAL;
    }

    void updateNode(Node *v) {
        v->val = oper(v->left->val, v->right->val);
        if (getVal(v->left) == v->val) {
            v->index = v->left->index;
        } else {
            v->index = v->right->index;
        }
    }

    void modify(Node *v, int ql, int qr, NumType val) {
        if (!v || v->l >= qr || v->r <= ql) {
            return;
        }
        v->propagate();
        if (v->l >= ql && v->r <= qr) {
            v->fSet = val;
            return;
        }
        modify(v->left, ql, qr, val);
        modify(v->right, ql, qr, val);
        v->left->propagate();
        v->right->propagate();
        updateNode(v);
    }

    pair<NumType, int> getValue(Node *v, int ql, int qr) {
        if (!v || v->l >= qr || v->r <= ql) {
            return {NEUTRAL, -1};
        }
        v->propagate();
        if (v->l >= ql && v->r <= qr) {
            return {v->val, v->index};
        }
        pair<NumType, int> res1 = getValue(v->left, ql, qr);
        pair<NumType, int> res2 = getValue(v->right, ql, qr);
        return res1.first < res2.first ? res1 : res2;
    }

public:
    SegmentTree() {
        root = nullptr;
        oper = nullptr;
    }

    explicit SegmentTree(int left_bnd, int right_bnd, NumType (*oper)(NumType &, NumType &)) {
        this->oper = oper;
        root = new Node(left_bnd, right_bnd);
    }

    pair<NumType, NumType> getQuery(int ql, int qr) {
        return getValue(root, ql, qr);
    }

    void modifyQuery(int ql, int qr, NumType val) {
        modify(root, ql, qr, val);
    }

};

SegmentTree<int> *tree;


int main() {
    int n, m;
    cin >> n >> m;
    tree = new SegmentTree<int>(0, n, [](int &a, int &b) { return min(a, b); });
    string query;
    int x1, x2;
    for (int i = 0; i ^ m; i++) {
        cin >> query >> x1 >> x2;
        if (query[0] == 'd') {
            int c;
            cin >> c;
            tree->modifyQuery(x1 - 1, x2, c);
        } else {
            pair<int, int> res = tree->getQuery(x1 - 1, x2);
            cout << res.first << " " << res.second + 1 << "\n";
        }
    }
}
