#include<iostream>
#include <vector>
#include <random>

using namespace std;

typedef long long LL;
const LL INF = 10000000000;

template<typename VertexData>
struct Vertex {
    VertexData value{};
    Vertex<VertexData> *ancestor{};
};

struct Job {
    int id;
    int duration;
    LL w;

    explicit Job() {
        this->id = this->duration = 0;
        this->w = 0;
    }

    [[nodiscard]] double costPerT() const {
        return ((double) w) / ((double) duration);
    }
};

struct VertexJob : public Vertex<Job *> {
    VertexJob *dependsOn;
    VertexJob *lastInSeq;

    explicit VertexJob() {
        this->value = nullptr;
        this->dependsOn = nullptr;
        this->ancestor = this;
        this->lastInSeq = this;
    }
};

template<typename T>
Vertex<T> *findDSU(Vertex<T> *x) {
    if (x && x->ancestor != x) {
        x->ancestor = findDSU(x->ancestor);
    }
    return x->ancestor;
}

template<typename T>
void unionDSU(Vertex<T> *x, Vertex<T> *y) {
    Vertex<T> *ax = findDSU(x);
    Vertex<T> *ay = findDSU(y);
// rank heuristic not always good
    ay->ancestor = ax;
}

int generateRand() {
    static mt19937 gen{random_device{}()};
    static uniform_int_distribution<int> distr(-10000, 10000);
    return distr(gen);
}

struct Vertex {
    int key;
    int prior;
    VertexJob *data;
    VertexJob *maxV;
    Vertex *left;
    Vertex *right;

    explicit Vertex(VertexJob *data) {
        this->key = data->value->id;
        this->prior = generateRand();
        this->data = this->maxV = data;
        this->left = this->right = nullptr;
    }

    [[nodiscard]] double getMaxValue() const {
        return this->maxV->value->costPerT();
    }

    void update() {
        this->maxV = this->data;
        if (this->left && this->left->getMaxValue() > this->getMaxValue()) {
            this->maxV = this->left->maxV;
        }
        if (this->right && this->right->getMaxValue() > this->getMaxValue()) {
            this->maxV = right->maxV;
        }
    }
};

Vertex *merge(Vertex *, Vertex *);

pair<Vertex *, Vertex *> split(Vertex *, int);


pair<Vertex *, Vertex *> split(Vertex *v, int id) {
    if (!v) {
        return {nullptr, nullptr};
    }
    if (v->key <= id) {
        pair<Vertex *, Vertex *> res = split(v->right, id);
        v->right = res.first;
        v->update();
        return {v, res.second};
    }
    pair<Vertex *, Vertex *> res = split(v->left, id);
    v->left = res.second;
    v->update();
    return {res.first, v};
}

Vertex *merge(Vertex *v1, Vertex *v2) {
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

Vertex *findSet(Vertex *v, int x) {
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

Vertex *insert(Vertex *v, VertexJob *x) {
    if (findSet(v, x->value->id)) {
        return v;
    }
    Vertex *newEl = new Vertex(x);
    pair<Vertex *, Vertex *> sp = split(v, newEl->key);
    return merge(merge(sp.first, newEl), sp.second);
}

Vertex *remove(Vertex *v, int id) {
    Vertex *res = findSet(v, id);
    if (!res) {
        return v;
    }
    pair<Vertex *, Vertex *> res1 = split(v, id - 1);
    pair<Vertex *, Vertex *> res2 = split(res1.second, id);
    return merge(res1.first, res2.second);
}

bool isEmpty(Vertex *v) {
    return !v;
}


void updateUntil(Vertex *v, int id) {
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

int n;
vector<VertexJob *> jobs;
VertexJob *root;
LL totalTime = 0;
vector<int> init_weight, init_dur;

void constructSchedule() {
    Vertex *set = nullptr;

    for (VertexJob *job: jobs) {
        if (!job->dependsOn) {
            job->value->w = -INF;
            root = job;
        } else {
            set = insert(set, job);
        }
    }

    while (!isEmpty(set)) {
        VertexJob *highest = set->maxV;
        set = remove(set, highest->value->id);
        auto *ancesF = (VertexJob *) (findDSU(highest->dependsOn));
        ancesF->value->w += highest->value->w;
        ancesF->value->duration += highest->value->duration;
        highest->dependsOn = ancesF->lastInSeq;
        ancesF->lastInSeq = highest->lastInSeq;
        unionDSU(findDSU(ancesF), findDSU(highest));
        updateUntil(set, ancesF->value->id);
    }

    vector<LL> schedule(n);
    VertexJob *cur = root->lastInSeq;
    LL wc = 0;
    while (cur) {
        wc += totalTime * init_weight[cur->value->id];
        totalTime -= init_dur[cur->value->id];
        schedule[cur->value->id] = totalTime;
        cur = cur->dependsOn;
    }

    cout << "\n" << wc << "\n";
    for (auto s: schedule) {
        cout << s << " ";
    }
}

int main() {
    freopen("p1outtreewc.in", "r", stdin);
    freopen("p1outtreewc.out", "w", stdout);
    cin >> n;
    jobs.resize(n);
    init_dur.resize(n);
    init_weight.resize(n);
    for (int i = 0; i ^ n; i++) {
        jobs[i] = new VertexJob();
        jobs[i]->value = new Job();
        jobs[i]->value->id = i;
        cin >> jobs[i]->value->duration;
        totalTime += jobs[i]->value->duration;
        init_dur[i] = jobs[i]->value->duration;
    }

    for (int i = 0; i ^ n; i++) {
        cin >> jobs[i]->value->w;

        init_weight[i] = jobs[i]->value->w;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        jobs[u - 1]->dependsOn = jobs[v - 1];
        if (!jobs[v - 1]->dependsOn) {
            root = jobs[v - 1];
        }
    }

    constructSchedule();
}