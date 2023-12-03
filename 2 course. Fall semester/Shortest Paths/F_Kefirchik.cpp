#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef long long LL;
int n, m;
vector<int> housesABC;
const LL NOROAD = 1000000000000000000;
vector<vector<pair<int, LL>>> bonds;


static LL minTriple(LL a, LL b, LL c) {
    LL mn = min(a, b);
    mn = min(mn, c);
    return mn;
}

static LL path(LL a, LL b, LL c) {
    return 2 * a + b + c;
}

static void getDistances(vector<LL> &dist, int s) {
    dist.assign(n, NOROAD);
    dist[s] = 0;
    set<pair<LL, int>> queue;
    queue.insert({0, s});
    while (!queue.empty()) {
        auto vpptr = queue.begin();
        int versh = vpptr->second;
        queue.erase(vpptr);
        for (const auto &c: bonds[versh]) {
            int child = c.first;
            LL len = c.second;
            if (dist[child] > dist[versh] + len) {
                if (queue.find({dist[child], child}) != queue.end())
                    queue.erase(queue.find({dist[child], child}));
                dist[child] = dist[versh] + len;
                queue.insert({dist[child], child});
            }
        }
    }
}

static vector<vector<LL>> distancesFromHouses() {
    vector<vector<LL>> distABC(3);
    for (int i = 0; i < 3; i++) {
        getDistances(distABC[i], housesABC[i]);
    }

    return distABC;
}

static LL optimalRoad(vector<vector<LL>> distances) {
    LL time = NOROAD;
    for (int i = 0; i < n; i++) {
        LL mint = minTriple(distances[0][i], distances[1][i], distances[2][i]);
        if (mint == NOROAD) {
            continue;
        }
        if (mint == distances[0][i]) {
            time = min(time, path(mint, distances[1][i], distances[2][i]));
        } else if (mint == distances[1][i]) {
            time = min(time, path(mint, distances[0][i], distances[2][i]));
        } else if (mint == distances[2][i]) {
            time = min(time, path(mint, distances[0][i], distances[1][i]));
        }
    }
    return time;
}

static void findKefir() {
    LL time = optimalRoad(distancesFromHouses());
    if (time == NOROAD) {
        time = -1;
    }
    cout << time;
}

static void init() {
    cin >> n >> m;

    bonds.resize(n);
    int versh, child;
    LL dist;
    for (int i = 0; i < m; i++) {
        cin >> versh >> child >> dist;
        bonds[versh - 1].emplace_back(child - 1, dist);
        bonds[child - 1].emplace_back(versh - 1, dist);
    }
    housesABC.resize(3);

    cin >> housesABC[0] >> housesABC[1] >> housesABC[2];
    housesABC[0]--;
    housesABC[1]--;
    housesABC[2]--;
}

int main() {
    init();
    findKefir();
}