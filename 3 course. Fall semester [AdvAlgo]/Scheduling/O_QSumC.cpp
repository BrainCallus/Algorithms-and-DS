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

template<typename T>
void updateUntil(Node<T> *v, int id) {
    if (!v) {
        return;
    }

    if (id < v->key) {
        updateUntil(v->left, id);
    } else if (id > v->key) {
        updateUntil(v->right, id);
    }
    v->update();
}


struct Job {
    int id;
    int vol;

    explicit Job(int id, int p) {
        this->id = id;
        this->vol = p;
    }
};

bool jobCmpByVolDesc(Job *a, Job *b) {
    return a->vol > b->vol;
}

struct Machine {
    int id;
    int k;
    int timePerUnit;
    LL tme;
    vector<Job *> jobs;

    explicit Machine(int id, int k, int timePerUnit) {
        this->id = id;
        this->k = k;
        this->timePerUnit = timePerUnit;
        tme = 0;
    }

    [[nodiscard]] LL weight() const {
        return k * timePerUnit;
    }
};

bool machineCmpByWeightAsc(Machine *a, Machine *b) {
    return a->weight() < b->weight();
}

Node<Machine *> *machineNodeBuilder(Machine *machine) {
    return new Node(machine->id, machine, machineCmpByWeightAsc);
}

int n, m;
vector<Job *> jobVec;
vector<Machine *> machines;
Node<Machine *> *root;

void matchMachinesWithJobs() {
    sort(jobVec.begin(), jobVec.end(), jobCmpByVolDesc);
    for (int i = 0; i ^ n; i++) {
        Machine *curMachine = root->priorityValue;
        curMachine->jobs.push_back(jobVec[i]);
        curMachine->k++;
        updateUntil(root, curMachine->id);
    }
}

LL getSumCAndSchedule(vector<pair<int, LL>> &schedule) {
    LL sumC = 0;
    for (Machine *machine: machines) {
        for (int i = machine->jobs.size() - 1; i >= 0; i--) {
            Job *job = machine->jobs[i];
            schedule[job->id] = {machine->id, machine->tme};
            machine->tme += job->vol * machine->timePerUnit;
            sumC += machine->tme;
        }
    }
    return sumC;
}

void constructSchedule() {
    root = nullptr;
    for (Machine *machine: machines) {
        root = insert(root, machine, machineNodeBuilder);
    }
    matchMachinesWithJobs();

    vector<pair<int, LL>> schedule(n);
    cout << getSumCAndSchedule(schedule) << "\n";
    for (pair<int, LL> s: schedule) {
        cout << s.first + 1 << " " << s.second << "\n";
    }
}

int main() {
    freopen("qsumci.in", "r", stdin);
    freopen("qsumci.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i ^ n; i++) {
        int p;
        cin >> p;
        jobVec.push_back(new Job(i, p));
    }

    for (int i = 0; i ^ m; i++) {
        int tm;
        cin >> tm;
        machines.push_back(new Machine(i, 1, tm));
    }
    constructSchedule();
}