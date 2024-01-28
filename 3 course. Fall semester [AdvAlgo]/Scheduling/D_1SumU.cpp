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
struct Vertex {
    int key;
    int prior;
    T data;
    T priorityValue;

    bool (*cmp)(T, T);

    Vertex<T> *left;
    Vertex<T> *right;

    explicit Vertex(int key, T data, bool (*cmp)(T, T)) {
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
Vertex<T> *merge(Vertex<T> *, Vertex<T> *);

template<typename T>
pair<Vertex<T> *, Vertex<T> *> split(Vertex<T> *, int);

template<typename T>
pair<Vertex<T> *, Vertex<T> *> split(Vertex<T> *v, int id) {
    if (!v) {
        return {nullptr, nullptr};
    }
    if (v->key <= id) {
        pair<Vertex<T> *, Vertex<T> *> res = split(v->right, id);
        v->right = res.first;
        v->update();
        return {v, res.second};
    }
    pair<Vertex<T> *, Vertex<T> *> res = split(v->left, id);
    v->left = res.second;
    v->update();
    return {res.first, v};
}

template<typename T>
Vertex<T> *merge(Vertex<T> *v1, Vertex<T> *v2) {
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
Vertex<T> *findSet(Vertex<T> *v, int x) {
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
Vertex<T> *insert(Vertex<T> *v, T x, Vertex<T> *(*nodeBuilder)(T)) {
    Vertex<T> *newEl = nodeBuilder(x);
    if (findSet(v, newEl->key)) {
        delete newEl;
        return v;
    }

    pair<Vertex<T> *, Vertex<T> *> sp = split(v, newEl->key);
    return merge(merge(sp.first, newEl), sp.second);
}

template<typename T>
Vertex<T> *remove(Vertex<T> *v, int id) {
    Vertex<T> *res = findSet(v, id);
    if (!res) {
        return v;
    }
    pair<Vertex<T> *, Vertex<T> *> res1 = split(v, id - 1);
    pair<Vertex<T> *, Vertex<T> *> res2 = split(res1.second, id);
    return merge(res1.first, res2.second);
}


struct Job {
    int id;
    int duration;
    int deadline;
    bool excluded;

    explicit Job(int id, int duration, int deadline) {
        this->id = id;
        this->duration = duration;
        this->deadline = deadline;
        this->excluded = false;
    }
};

bool jobCmpLateCostAsc(Job *a, Job *b) {
    return a->duration > b->duration;
}

bool jobCmpDeadlineAsc(Job *a, Job *b) {
    return a->deadline < b->deadline;
}

Vertex<Job *> *jobNodeBuilder(Job *job) {
    return new Vertex<Job *>(job->id, job, jobCmpLateCostAsc);
}

vector<Job *> jobs;
Vertex<Job *> *root;
int n;

void defineExcludedJobs() {
    LL t = 0;
    root = nullptr;
    sort(jobs.begin(), jobs.end(), jobCmpDeadlineAsc);

    for (int i = 0; i ^ n; i++) {
        t += jobs[i]->duration;
        root = insert(root, jobs[i], jobNodeBuilder);
        if (t > jobs[i]->deadline) {
            Job *toRemove = root->priorityValue;
            toRemove->excluded = true;
            root = remove(root, toRemove->id);
            t -= toRemove->duration;
        }
    }
}

void constructSchedule() {
    defineExcludedJobs();

    vector<LL> schedule(n, 0);
    LL t = 0;
    int cnt = 0;
    for (Job *job: jobs) {
        if (job->excluded) {
            schedule[job->id] = -1;
        } else {
            schedule[job->id] = t;
            t += job->duration;
            cnt++;
        }
    }

    cout << cnt << "\n";
    for (LL s: schedule) {
        cout << s << " ";
    }
}

int main() {
    freopen("p1sumu.in", "r", stdin);
    freopen("p1sumu.out", "w", stdout);
    cin >> n;
    jobs.resize(n);
    for (int i = 0; i ^ n; i++) {
        int d, dl;
        cin >> d >> dl;
        jobs[i] = new Job(i, d, dl);
    }
    constructSchedule();
}