#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Job {
    int id;
    int deadline;
    int ancestor_end;
    Job *child;
    vector<Job *> ancestors;

    explicit Job(int id, int deadline) {
        this->id = id;
        this->deadline = deadline;
        ancestor_end = 0;
        child = nullptr;
    }
};

bool jobCmpDeadlineAsc(Job *a, Job *b) {
    return a->deadline < b->deadline;
}

Job *bottom;
vector<Job *> jobs;
int n, m;

void recalcDeadlines() {
    queue<Job *> q;
    q.push(bottom);
    while (!q.empty()) {
        Job *cur = q.front();
        q.pop();
        for (Job *ancestor: cur->ancestors) {
            ancestor->deadline = min(ancestor->deadline, cur->deadline - 1);
            q.push(ancestor);
        }
    }
}

void defineBottom() {
    for (Job *job: jobs) {
        if (!job->child) {
            bottom = job;
            break;
        }
    }
}

void constructSchedule() {
    defineBottom();
    recalcDeadlines();
    sort(jobs.begin(), jobs.end(), jobCmpDeadlineAsc);
    vector<int> ready(n + 1, 0);
    vector<int> schedule(n);
    int f = 0;
    int lMax = -1000000000;
    int t;
    for (int i = 0; i ^ n; i++) {
        t = max(jobs[i]->ancestor_end, f);
        schedule[jobs[i]->id] = t;
        lMax = max(lMax, schedule[jobs[i]->id] + 1 - jobs[i]->deadline);

        ready[t]++;
        if (ready[t] == m) {
            f = t + 1;
        }

        if (jobs[i]->child) {
            jobs[i]->child->ancestor_end = max(jobs[i]->child->ancestor_end, t + 1);
        }
    }

    cout << lMax << "\n";
    for (int s: schedule) {
        cout << s << " ";
    }
}

int main() {
    freopen("pintreep1l.in", "r", stdin);
    freopen("pintreep1l.out", "w", stdout);
    cin >> n >> m;
    jobs.resize(n);
    for (int i = 0; i ^ n; i++) {
        int d;
        cin >> d;
        jobs[i] = new Job(i, d);
    }
    for (int i = 0; i ^ (n - 1); i++) {
        int x, y;
        cin >> x >> y;
        jobs[x - 1]->child = jobs[y - 1];
        jobs[y - 1]->ancestors.push_back(jobs[x - 1]);
    }
    constructSchedule();
}
