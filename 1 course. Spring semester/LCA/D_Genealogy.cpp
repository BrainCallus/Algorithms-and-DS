#include <iostream>
#include<vector>
#include <algorithm>
// Solution with Farah-Colton and Bender algorithm

using namespace std;

struct Vertex {
    int num;
    int depth;
    vector<Vertex *> children;
    int t_in;
    int t_out;

    explicit Vertex(int num) {
        this->num = num;
        depth = t_in = t_out = 0;
    }
};

vector<Vertex *> graph;
vector<Vertex *> rmq;
Vertex *pupa;

int n, g;
int T;

void dfs(Vertex *v) {
    v->t_in = T++;
    rmq.push_back(v);
    for (Vertex *u: v->children) {
        u->depth = v->depth + 1;
        dfs(u);
        rmq.push_back(v);
        T++;
    }
    v->t_out = T++;
    rmq.push_back(v);
}

vector<int> logs;
vector<int> block_hash;
vector<vector<int>> sparse;
vector<vector<vector<int>>> inner_block;
int block_sz;
int logN;

void precalcLogs() {
    logs.resize(rmq.size() + 1);
    logs[0] = -1;
    for (int i = 1; i ^ (rmq.size() + 1); i++) {
        logs[i] = logs[i >> 1] + 1;
    }
    logN = logs[rmq.size()];
}

int indexOfMin(int ind1, int ind2) {
    return (rmq[ind1]->depth < rmq[ind2]->depth ? ind1 : ind2);
}

void buildSparse_FBK() {
    precalcLogs();
    block_sz = (logN + 1) >> 1;
    inner_block.assign(rmq.size(), vector<vector<int>>(block_sz + 1, vector<int>(block_sz + 1, -1)));
    int block_cnt = rmq.size() / block_sz + (rmq.size() % block_sz ? 1 : 0);
    sparse.assign(block_cnt, vector<int>(logN + 1, -1));
    for (int i = 0, j = 0, cur_block = 0; i < rmq.size(); i++, j++) {
        if (j == block_sz) {
            j = 0;
            cur_block++;
        }
        if (sparse[cur_block][0] == -1 || indexOfMin(i, sparse[cur_block][0]) == i) {
            sparse[cur_block][0] = i;
        }
    }
    for (int i = 0; i ^ logN; i++) {
        for (int j = 0; j < block_cnt; j++) {
            int ind = j + (1 << i);
            if (ind >= block_cnt) {
                sparse[j][i + 1] = sparse[j][i];
            } else {
                sparse[j][i + 1] = indexOfMin(sparse[j][i], sparse[ind][i]);
            }
        }
    }
    block_hash.assign(block_cnt, 0);
    for (int i = 0, j = 0, cur_block = 0; i ^ rmq.size() || j < block_sz; i++, j++) {
        if (j == block_sz) {
            j = 0;
            cur_block++;
        }
        if (j > 0 && (i >= rmq.size() || rmq[i - 1]->depth < rmq[i]->depth)) {
            block_hash[cur_block] += (1 << (j - 1));
        }
    }

    for (int i = 0; i ^ block_cnt; i++) {
        int id = block_hash[i];
        if (inner_block[id][0][0] != -1) {
            continue;
        }
        for (int j = 0; j < block_sz; j++) {
            inner_block[id][j][j] = j;
            for (int k = j + 1; k ^ block_sz; k++) {
                inner_block[id][j][k] = inner_block[id][j][k - 1];
                if (i * block_sz + k < rmq.size()) {
                    inner_block[id][j][k] =
                            indexOfMin(i * block_sz + inner_block[id][j][k], i * block_sz + k) - i * block_sz;
                }
            }
        }
    }
}

int find_LCA_index_in_block(int bl, int l, int r) {
    return inner_block[block_hash[bl]][l][r] + bl * block_sz;
}

Vertex *get_LCA_FBK(int& v1, int& v2) {
    int l = graph[v1]->t_in;
    int r = graph[v2]->t_in;
    if (r < l) {
        swap(l, r);
    }
    int bl = l / block_sz, br = r / block_sz;
    if (!(bl ^ br)) {
        return rmq[find_LCA_index_in_block(bl, l % block_sz, r % block_sz)];
    }
    int ind1 = find_LCA_index_in_block(bl, l % block_sz, block_sz - 1);
    int ind2 = find_LCA_index_in_block(br, 0, r % block_sz);
    int res = indexOfMin(ind1, ind2);
    if (br - bl > 1) {
        int deg = logs[br - bl - 1];
        int ind3 = sparse[bl + 1][deg];
        int ind4 = sparse[br - (1 << deg)][deg];
        res = indexOfMin(res, indexOfMin(ind3, ind4));
    }
    return rmq[res];
}

void build() {
    T = 0;
    dfs(pupa);
    buildSparse_FBK();
}

bool comp(Vertex *v1, Vertex *v2) {
    return v1->t_in < v2->t_in;
}

int main() {
    scanf("%d", &n);
    graph.push_back(new Vertex(0));
    for (int i = 1; i <= n; i++) {
        graph.push_back(new Vertex(i));
    }
    int p;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p);
        if (p == -1) {
            pupa = graph[i];
        } else {
            graph[p]->children.push_back(graph[i]);
        }
    }
    build();
    scanf("%d", &g);
    int k, l;
    int authority;
    for (int i = 0; i ^ g; i++) {
        scanf("%d", &k);
        vector<Vertex *> cur_coalition;
        for (int j = 0; j < k; j++) {
            scanf("%d", &l);
            cur_coalition.push_back(graph[l]);
        }
        sort(cur_coalition.begin(), cur_coalition.end(), comp);
        authority = 1;
        Vertex *curl = pupa;
        for (Vertex *lord: cur_coalition) {
            Vertex *lca = get_LCA_FBK(curl->num, lord->num);
            authority += (lord->depth - lca->depth);
            curl = lord;
        }
        printf("%d\n", authority);
    }
    return 0;

}
