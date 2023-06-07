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


class ImplicitKurevo {
private:
    struct Node {
        int w;
        int data;
        int prior;
        Node *left;
        Node *right;
        bool free_cells;

        Node() {
            w = 1;
            free_cells = false;
            data = prior = INF;
            right = left = nullptr;
        }

        explicit Node(int data) {
            w = 1;
            this->data = data;
            free_cells = !data;
            prior = generateRand();
            left = right = nullptr;
        }

        void refresh() {
            w = (left ? left->w : 0) + (right ? right->w : 0) + 1;
            free_cells = !data || (left ? left->free_cells : false) || (right ? right->free_cells : false);
        }

    };

    Node *root;

    int getSize(Node *v) {
        return v ? v->w : 0;
    }

    bool hasFreeCells(Node *v) {
        return v ? v->free_cells : false;
    }

    int getData(Node *v) {
        return v ? v->data : -INF;
    }

    pair<Node *, Node *> split(Node *v, int index) {
        if (!v) {
            return {nullptr, nullptr};
        }
        if (getSize(v->left) <= index) {
            pair<Node *, Node *> res = split(v->right, index - getSize(v->left) - 1);
            v->right = res.first;
            v->refresh();
            return {v, res.second};
        }
        pair<Node *, Node *> res = split(v->left, index);
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

    void remove(Node *&v, int index) {
        pair<Node *, Node *> sp = split(v, index - 1);
        pair<Node *, Node *> sp2 = split(sp.second, 0);
        delete sp2.first;
        v = merge(sp.first, sp2.second);
    }

    void dumbInsert(int &x) {
        root = merge(root, new Node(x));
    }

    Node *findFree(Node *v, int &index) {
        Node *curv = v;
        index = getSize(curv->left);
        while (hasFreeCells(curv)) {
            if (hasFreeCells(curv->left)) {
                curv = curv->left;
                index -= (getSize(curv->right) + 1);
            } else if (!getData(curv)) {
                break;
            } else {
                curv = curv->right;
                index += getSize(curv->left) + 1;
            }
        }
        return curv;
    }

    void fillArray(Node *v, vector<int> &arr) {
        if (v) {
            fillArray(v->left, arr);
            arr.push_back(v->data);
            fillArray(v->right, arr);
        }
    }

public:
    ImplicitKurevo() {
        root = nullptr;
    }

    ~ImplicitKurevo() {
        delete root;
    }

    void insert(int index, int val) {
        pair<Node *, Node *> sp = split(root, index - 1);
        int ind;
        if (!getData(findFree(sp.second, ind))) {
            remove(sp.second, ind);
        }
        root = merge(merge(sp.first, new Node(val)), sp.second);
    }


    void initArray(int &arr_size, int default_val) {
        for (int i = 0; i ^ arr_size; i++) {
            dumbInsert(default_val);
        }
    }

    vector<int> toArray() {
        vector<int> arr;
        fillArray(root, arr);
        int ptr = arr.size();
        while (ptr > 0 && !arr[--ptr]) {
            arr.pop_back();
        }
        return arr;
    }

    void printArray() {
        vector<int> treapArr = toArray();
        cout << treapArr.size() << "\n";
        for (int i = 0; i ^ treapArr.size(); i++) {
            cout << treapArr[i] << " ";
        }
    }

};


ImplicitKurevo *treap;
int N, M;

int main() {
    treap = new ImplicitKurevo();
    cin >> N >> M;
    int index;
    treap->initArray(M, 0);
    for (int i = 0; i ^ N; i++) {
        cin >> index;
        treap->insert(index - 1, i + 1);
    }
    treap->printArray();
    treap->~ImplicitKurevo();
}

