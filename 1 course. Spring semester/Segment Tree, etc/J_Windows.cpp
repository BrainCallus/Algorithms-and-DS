#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 2 * 100000 + 1;

const int NEUTRAL = 0;
int n;

struct Point {
    int x;
    int y_bottom;
    int y_top;
    int adder;

    Point(int x, int y_bottom, int y_top, int adder) {
        this->x = x;
        this->y_bottom = y_bottom;
        this->y_top = y_top;
        this->adder = adder;
    }

    static int getInitialVal() {
        return 0;
    }
};

bool comp(Point *a, Point *b) {
    return a->x < b->x || (a->x == b->x && a->adder > b->adder);
}

struct Node {
    int val = NEUTRAL - 1;
    int l, r;
    int fAdd = NEUTRAL;
    int indexMax;

    int (*oper)(int, int);

    Node *left = nullptr;
    Node *right = nullptr;

    template<typename T>
    explicit Node(int l, int r, vector<T *> &arr, int (*oper)(int, int)) {
        this->l = l;
        this->r = r;
        this->oper = oper;
        if (r - l > 1) {
            int mid = l + ((r - l) >> 1);
            left = new Node(l, mid, arr, oper);
            right = new Node(mid, r, arr, oper);
            val = left->val + right->val;
        } else {
            val = arr[l]->getInitialVal();
        }
        indexMax = l;
    }

    void propagate() {
        if (fAdd) {
            val += fAdd;
            if (r - l > 1) {
                left->fAdd += fAdd;
                right->fAdd += fAdd;
            }
            fAdd = NEUTRAL;
        }
    }

    void update() {
        val = oper((left ? left->val : 0), (right ? right->val : 0));
        if (left) {
            indexMax = left->val > right->val ? left->indexMax : right->indexMax;
        } else {
            indexMax = l;
        }
    }

    int getValue() const {
        return val + fAdd;
    }
};

vector<Point *> points;
Node *tree;

int operation_max(int a, int b) {
    return a > b ? a : b;
}

void modify(Node *v, int ql, int qr, int delta) {
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
    v->update();
}

int main() {
    cin >> n;
    int x1, x2, y1, y2;
    int max_points = 0, maxX = 0, maxY = -INF;
    int shift = INF;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        shift = min(shift, y1);
        maxY = max(maxY, y2);
        points.push_back(new Point(x1, y1, y2, 1));
        points.push_back(new Point(x2, y1, y2, -1));
    }
    sort(points.begin(), points.end(), comp);
    tree = new Node(0, maxY - shift + 1, points, operation_max);


    maxY = points[0]->y_bottom;
    maxX = points[0]->x;
    for (int i = 0; i < (n << 1); i++) {
        modify(tree, points[i]->y_bottom - shift, points[i]->y_top - shift + 1, points[i]->adder);
        if (points[i]->adder == 1 && tree->getValue() > max_points) {
            max_points = tree->getValue();
            maxX = points[i]->x;
            maxY = tree->indexMax; //tree updated in modify
        }
    }
    cout << max_points << "\n";
    cout << maxX << " " << maxY + shift;
}