#include <iostream>
#include<vector>
#include<random>
#include <algorithm>

using namespace std;

const int INF = 2000000000;

struct Node {
    int val = INF;
    int data = 0; // number in sequence
    int prior = INF;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *ancestor = nullptr;

    Node() = default;

    explicit Node(int val, int prior, int data) {
        this->val = val;
        this->data = data;
        this->prior = prior;
        right = left = ancestor = nullptr;
    }
};

int N;
vector<Node *> nodes, unsorted;

bool comparator(Node *a, Node *b) {
    return a->val > b->val;
}


void insertAbove(Node *&upper, Node *&lower) {
    upper->left = lower;
    lower->ancestor = upper;
}

void insertBelow(Node *&upper, Node *&lower) {
    lower->left = upper->right;
    upper->right->ancestor = lower;
    lower->ancestor = upper;
    upper->right = lower;
}

void makeRight(Node *&curv, int &ptr) {
    Node *leftNode = curv;
    while (leftNode->ancestor && leftNode->prior < nodes[ptr]->prior) {
        leftNode = leftNode->ancestor;
    }
    curv = nodes[ptr];
    if (leftNode->prior < nodes[ptr]->prior) {
        insertAbove(curv, leftNode);
    } else {
        insertBelow(leftNode, curv);
    }
}

void makeLeft(Node *&curv, int &ptr) {
    curv->right = nodes[ptr];
    curv->right->ancestor = curv;
    curv = curv->right;
}

void buildCarthesian() {
    Node *curv = nodes[0];
    vector<int> priors;
    for (Node *v: nodes) {
        priors.push_back(v->prior);
    }
    int ptr = 0;
    while (++ptr ^ N) {
        if (curv->prior > priors[ptr]) {
            makeLeft(curv, ptr);
        } else {
            makeRight(curv, ptr);
        }

    }
}

void printCarthesian() {
    cout << "YES\n";
    for (Node *v: unsorted) {
        cout << (v->ancestor ? v->ancestor->data : 0) << " "
             << (v->left ? v->left->data : 0) << " "
             << (v->right ? v->right->data : 0) << "\n";
    }
}

int main() {
    cin >> N;
    int x, y;
    for (int i = 1; i <= N; i++) {
        cin >> x >> y;
        nodes.push_back(new Node(-x, -y, i));
        unsorted.push_back(nodes[nodes.size() - 1]);
    }
    sort(nodes.begin(), nodes.end(), comparator);
    buildCarthesian();
    printCarthesian();
}


