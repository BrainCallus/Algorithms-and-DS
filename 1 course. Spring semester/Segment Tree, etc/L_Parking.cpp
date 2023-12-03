#include <iostream>
#include<vector>

using namespace std;

const int MIN_NEUTRAL = 10000000;


template<typename NumType>
class SegmentTree {
private:
    NumType NEUTRAL;

    NumType (*oper)(NumType, NumType);

    struct Node {
        NumType minn;
        int l, r;
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
            minn = l;
        }
    };

    Node *root;

    void updateNode(Node *v) {
        v->minn = oper((v->left ? v->left->minn : NEUTRAL), (v->right ? v->right->minn : NEUTRAL));
    }

    NumType getValue(Node *v, int ql, int qr) {
        if (!v || v->l >= qr || v->r <= ql) {
            return NEUTRAL;
        }
        if (v->l >= ql && v->r <= qr) {
            return v->minn;
        }

        return oper(getValue(v->left, ql, qr), getValue(v->right, ql, qr));
    }

    void modify(Node *v, int ql, int qr, NumType val) {
        if (!v || v->l >= qr || v->r <= ql) {
            return;
        }
        if (v->l >= ql && v->r <= qr) {
            v->minn = val;
            return;
        }
        modify(v->left, ql, qr, val);
        modify(v->right, ql, qr, val);
        updateNode(v);
    }

public:
    SegmentTree() {
        this->NEUTRAL = nullptr;
        this->oper = std::min;
        root = nullptr;
    }

    explicit SegmentTree(int left_bnd, int right_bnd, NumType NEUTRAL, NumType (oper)(NumType, NumType)) {
        this->NEUTRAL = NEUTRAL;
        this->oper = oper;

        root = new Node(left_bnd, right_bnd);
    }

    int getSize() {
        return root->r - root->l;
    }

    NumType getQuery(int l, int r) {
        return getValue(root, l, r);
    }

    void modifyQuery(int l, int r, NumType val) {
        modify(root, l, r, val);
    }
};

SegmentTree<int> *tree;


void enter(int &place) {
    int first_free = tree->getQuery(place - 1, tree->getSize());
    if (first_free == MIN_NEUTRAL) {
        first_free = tree->getQuery(0, place - 1);
    }
    tree->modifyQuery(first_free, first_free + 1, MIN_NEUTRAL);
    cout << first_free + 1 << "\n";
}

void leave(int &place) {
    tree->modifyQuery(place - 1, place, place - 1);
}

int n, m;

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    cin >> n >> m;
    tree = new SegmentTree<int>(0, n, MIN_NEUTRAL, [](int a, int b) { return min(a, b); });

    string query;
    int place;
    for (int i = 0; i < m; i++) {
        cin >> query >> place;
        if (query[1] == 'n') {
            enter(place);
        } else {
            leave(place);
        }
    }
}
