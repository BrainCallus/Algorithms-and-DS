#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

typedef long long LL;

int generateRand() {
    static mt19937 gen{random_device{}()};
    static uniform_int_distribution<int> distr(-10000, 10000);
    return distr(gen);
}

template<typename T>
struct Node {
    int key;
    int prior;
    T data;
    T priorityValue;

    bool (*cmp)(T, T);

    Node<T> *left;
    Node<T> *right;

    explicit Node(int key, T data, bool (*cmp)(T, T)) {
        this->key = key;
        this->data = this->priorityValue = data;
        this->cmp = cmp;
        this->prior = generateRand();
        this->left = this->right = nullptr;
    }

    void update() {
        this->priorityValue = this->data;
        if (left && cmp(left->priorityValue, this->priorityValue)) {
            this->priorityValue = left->priorityValue;
        }
        if (right && cmp(right->priorityValue, this->priorityValue)) {
            this->priorityValue = right->priorityValue;
        }
    }
};

template<typename T>
Node<T> *merge(Node<T> *, Node<T> *);

template<typename T>
pair<Node<T> *, Node<T> *> split(Node<T> *, int);

template<typename T>
pair<Node<T> *, Node<T> *> split(Node<T> *v, int id) {
    if (!v) {
        return {nullptr, nullptr};
    }
    if (v->key <= id) {
        pair<Node<T> *, Node<T> *> res = split(v->right, id);
        v->right = res.first;
        v->update();
        return {v, res.second};
    }
    pair<Node<T> *, Node<T> *> res = split(v->left, id);
    v->left = res.second;
    v->update();
    return {res.first, v};
}

template<typename T>
Node<T> *merge(Node<T> *v1, Node<T> *v2) {
    if (!v2) {
        return v1;
    }
    if (!v1) {
        return v2;
    }

    if (v1->prior > v2->prior) {
        v1->right = merge(v1->right, v2);
        v1->update();
        return v1;
    }

    v2->left = merge(v1, v2->left);
    v2->update();
    return v2;
}

template<typename T>
Node<T> *findSet(Node<T> *v, int x) {
    if (!v) {
        return nullptr;
    }
    if (x == v->key) {
        return v;
    }
    if (x < v->key) {
        return findSet(v->left, x);
    }
    return findSet(v->right, x);
}

template<typename T>
Node<T> *insert(Node<T> *v, T x, Node<T> *(*nodeBuilder)(T)) {
    Node<T> *newEl = nodeBuilder(x);
    if (findSet(v, newEl->key)) {
        delete newEl;
        return v;
    }

    pair<Node<T> *, Node<T> *> sp = split(v, newEl->key);
    return merge(merge(sp.first, newEl), sp.second);
}

template<typename T>
Node<T> *remove(Node<T> *v, int id) {
    Node<T> *res = findSet(v, id);
    if (!res) {
        return v;
    }
    pair<Node<T> *, Node<T> *> res1 = split(v, id - 1);
    pair<Node<T> *, Node<T> *> res2 = split(res1.second, id);
    return merge(res1.first, res2.second);
}


struct Job {
    int id;
    int duration1;
    int duration2;
    LL end1;
    LL end2;

    explicit Job(int id, int p1) {
        this->id = id;
        this->duration2 = this->duration1 = p1;
    }

    [[nodiscard]] bool p1Min() const {
        return duration1 < duration2;
    }
};

bool jobCmpPAsc(Job *a, Job *b) {
    return min(a->duration1, a->duration2) < min(b->duration2, b->duration1);
}

Node<Job *> *jobNodeBuilder(Job *job) {
    return new Node<Job *>(job->id, job, jobCmpPAsc);
}

int n;
vector<Job *> jobs;
Node<Job *> *root = nullptr;

void findOptimalJobSeq(vector<Job *> &left, vector<Job *> &rightRev) {
    for (int i = 0; i ^ n; i++) {
        Job *job = root->priorityValue;
        if (job->p1Min()) {
            left.push_back(job);
        } else {
            rightRev.push_back(job);
        }
        root = remove(root, job->id);
    }
    reverse(rightRev.begin(), rightRev.end());
}

void calcLeftSchedule(vector<Job *> &left) {
    if (!left.empty()) {
        left[0]->end1 = left[0]->duration1;
        left[0]->end2 = left[0]->end1 + left[0]->duration2;
    }
    for (int i = 1; i ^ left.size(); i++) {
        left[i]->end1 = left[i - 1]->end1 + left[i]->duration1;
        left[i]->end2 = max(left[i - 1]->end2, left[i]->end1) + left[i]->duration2;
    }
}

void calcRightSchedule(vector<Job *> &left, vector<Job *> &right) {
    if (!right.empty()) {
        right[0]->end1 = (left.empty() ? 0 : left[left.size() - 1]->end1) + right[0]->duration1;

        right[0]->end2 = (left.empty() ? right[0]->end1 : max(right[0]->end1, left[left.size() - 1]->end2)) +
                         right[0]->duration2;
    }
    for (int i = 1; i < right.size(); i++) {
        right[i]->end1 = right[i - 1]->end1 + right[i]->duration1;
        right[i]->end2 = max(right[i - 1]->end2, right[i]->end1) + right[i]->duration2;
    }
}

void printSchedule(vector<Job *> &jobSeq) {
    for (auto &job: jobSeq) {
        cout << job->id + 1 << " ";
    }
}

void constructSchedule() {
    vector<Job *> left, right;
    findOptimalJobSeq(left, right);
    calcLeftSchedule(left);
    calcRightSchedule(left, right);

    cout << (right.empty() ? left[left.size() - 1]->end2 : right[right.size() - 1]->end2) << "\n";
    for (int k = 0; k ^ 2; k++) {
        printSchedule(left);
        printSchedule(right);
        cout << "\n";
    }
}

int main() {
    freopen("f2cmax.in", "r", stdin);
    freopen("f2cmax.out", "w", stdout);
    cin >> n;
    for (int i = 0; i ^ n; i++) {
        int d1;
        cin >> d1;
        jobs.push_back(new Job(i, d1));
    }
    for (int i = 0; i ^ n; i++) {
        int d2;
        cin >> d2;
        jobs[i]->duration2 = d2;
        root = insert(root, jobs[i], jobNodeBuilder);
    }
    constructSchedule();
}