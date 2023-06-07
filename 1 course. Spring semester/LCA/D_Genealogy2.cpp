#include <iostream>
#include<vector>
// Solution with HLD, better int terms of time and memory usage

using namespace std;


struct Vertex {
    int w=1;
    int num=0;
    int depth=0;
    int max_depth=-1;
    Vertex *link= nullptr;
    Vertex *heavy= nullptr;
    Vertex *ancestor= nullptr;
    vector<Vertex *> children;

    explicit Vertex(int num) {
        this->num = num;
    }
    Vertex()= default;
};

vector<Vertex> graph;
Vertex *pupa;
int cur = 1, pos = 0;
vector<int> position;
vector<Vertex *> sequential;

int n, g;

void dfs(Vertex *v) {
    for (Vertex *u: v->children) {
        u->depth = v->depth + 1;
        dfs(u);
        v->w += u->w;
        if (!v->heavy || v->heavy->w < u->w) {
            v->heavy = u;
        }
    }
}

void HLD(Vertex *v) {
    sequential[cur] = v;
    if (position.size() <= pos) {
        position.push_back(cur);
    }
    cur++;
    v->link = &graph[pos];
    if (v->heavy) {
        HLD(v->heavy);
    }
    for (Vertex *u: v->children) {
        if (u != v->heavy) {
            pos++;
            HLD(u);
        }
    }
}

vector<int> coalition;

int max(int a, int b){
    return a>=b?a:b;
}

void getAuthority(int cur_group, Vertex *lord, int &authority) {
    while (lord) {
        Vertex *curl = sequential[position[lord->link->num]];
        if (coalition[curl->num] < cur_group) {
            curl->max_depth = curl->depth;
        }
        authority += max(0, lord->depth - curl->max_depth + 1);
        curl->max_depth = max(curl->max_depth, lord->depth + 1);
        coalition[curl->num] = cur_group;
        lord = curl->ancestor;
    }
}

void build() {
    dfs(pupa);
    sequential.assign(n + 1, pupa);
    HLD(pupa);
}


int main() {
    scanf("%d",&n);
    int i;
    graph.resize(n+1);
    int p;
    for (i = 1; i ^ n + 1; ++i) {
        scanf("%d",&p);
        graph[i].num=i;
        if (p == -1) {
            pupa = &graph[i];
        } else {
            graph[p].children.push_back(&graph[i]);
            graph[i].ancestor = &graph[p];
        }
    }
    build();
    scanf("%d",&g);
    coalition.resize(n + 1, -1);
    int k, l;
    int authority = 0;
    for (i = 0; i ^ g; ++i) {
        scanf("%d",&k);
        authority ^= authority;
        for (int j = 0; j ^ k; ++j) {
            scanf("%d",&l);
            getAuthority(i, &graph[l], authority);
        }
        printf("%d\n",authority);
    }

}
