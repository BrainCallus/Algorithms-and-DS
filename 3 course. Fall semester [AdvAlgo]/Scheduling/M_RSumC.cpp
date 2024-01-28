#include<iostream>
#include <vector>
#import <queue>
#include <unordered_map>

using namespace std;

typedef long long LL;
static const LL INF = 10000000000000000;

struct Machine {
    int id;
    int k;
    vector<int> jobIds;

    explicit Machine(int id) {
        this->id = id;
        k = 0;
    }
};

struct Vertex;
struct Edge;

struct Edge {
    LL cost;
    LL flow;
    LL capacity;
    Vertex *end;

    explicit Edge(Vertex *end, LL cost, LL capacity) {
        this->end = end;
        this->cost = cost;
        this->capacity = capacity;
        flow = 0;
    }
};

struct Vertex {
    int id;
    unordered_map<int, Edge *> edges;
    Vertex *pred;
    bool mark;
    LL dist;
    pair<int, int> mId;

    explicit Vertex(int id) {
        this->id = id;
        this->dist = INF;
        pred = nullptr;
        mark = false;
        mId = {-1, -1};
    }
};

void addEdge(Vertex *u, Vertex *v, LL cap, LL cost) {
    u->edges[v->id] = new Edge(v, cost, cap);
    v->edges[u->id] = new Edge(u, -cost, 0);
}


int GS;
int n, m;
vector<Vertex *> graph;
vector<Machine *> machines;

void refreshNodes() {
    for (Vertex *v: graph) {
        v->dist = INF;
        v->mark = false;
        v->pred = nullptr;
    }
}

void shortestPath() {
    refreshNodes();
    graph[0]->dist = 0;
    queue<Vertex *> q;
    q.push(graph[0]);

    while (!q.empty()) {
        Vertex *u = q.front();
        q.pop();
        u->mark = false;
        for (pair<int, Edge *> e: u->edges) {
            Vertex *v = e.second->end;
            if (e.second->capacity > 0 && v->dist > u->dist + e.second->cost) {
                v->dist = u->dist + e.second->cost;
                v->pred = u;
                if (!v->mark) {
                    v->mark = true;
                    q.push(v);
                }
            }
        }
    }
}

LL getFlowDelta(Vertex *cur, LL &flow) {
    LL fDelta = INF - flow;
    while (cur->id) {
        fDelta = min(fDelta, cur->pred->edges[cur->id]->capacity);
        cur = cur->pred;
    }
    flow += fDelta;
    return fDelta;
}

void updateNetwork(Vertex *cur, LL &fDelta) {
    while (cur->id) {
        cur->pred->edges[cur->id]->capacity -= fDelta;
        cur->pred->edges[cur->id]->flow += fDelta;
        cur->edges[cur->pred->id]->capacity += fDelta;
        cur->edges[cur->pred->id]->flow -= fDelta;
        cur = cur->pred;
    }
}

LL minCostFlow() {
    LL flow = 0;
    LL cost = 0;
    Vertex *t = graph[GS + 1];
    while (flow < INF) {
        shortestPath();
        if (t->dist == INF) {
            break;
        }

        Vertex *cur = t;
        LL fDelta = getFlowDelta(cur, flow);
        cost += fDelta * t->dist;
        cur = t;
        updateNetwork(cur, fDelta);
    }
    return cost;
}

void matchMachinesWithJobs() {
    for (int i = 0; i ^ n; i++) {
        for (pair<int, Edge *> rib: graph[i + 1]->edges) {
            if (rib.second->flow > 0) {
                pair<int, int> mid = rib.second->end->mId;
                machines[mid.first]->jobIds[mid.second] = graph[i + 1]->id;
                machines[mid.first]->k++;
                break;
            }
        }
    }
}

void constructSchedule() {
    cout << minCostFlow() << "\n";
    matchMachinesWithJobs();

    for (Machine *machine: machines) {
        cout << machine->k << " ";
        for (int i = machine->jobIds.size() - 1; i >= 0; i--) {
            if (machine->jobIds[i] < 0) {
                continue;
            }
            cout << machine->jobIds[i] << " ";
        }
        cout << "\n";
    }
}

void addInnerRibs() {
    for (int i = 0; i ^ n; i++) {
        for (int j = 0; j ^ m; j++) {
            int pij;
            cin >> pij;
            for (int k = 0; k ^ n; k++) {
                int idx = j * n + k + n + 1;
                addEdge(graph[i + 1], graph[idx], 1, (k + 1) * pij);
                addEdge(graph[idx], graph[GS + 1], 1, 0);
                graph[idx]->mId = {machines[j]->id, k};
            }
        }
    }
}

void initGraph() {
    graph.resize(GS + 2);

    for (int i = 0; i ^ (GS + 2); i++) {
        graph[i] = new Vertex(i);
    }
    for (int i = 1; i <= n; i++) {
        addEdge(graph[0], graph[i], 1, 0);
    }
    for (int i = 0; i ^ m; i++) {
        machines.push_back(new Machine(i));
        machines[i]->jobIds.assign(n, -1);
    }
    addInnerRibs();
}

int main() {
    freopen("rsumc.in", "r", stdin);
    freopen("rsumc.out", "w", stdout);
    cin >> n >> m;
    GS = n * m + n;
    initGraph();
    constructSchedule();
}