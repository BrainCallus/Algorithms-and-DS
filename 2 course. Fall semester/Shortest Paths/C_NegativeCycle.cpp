#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<long long> dist, p;

class Rib {
public:
    int start;
    int end;
    long long len;

    explicit Rib(int s = -1, int e = -1, long long w = -1);

};

Rib::Rib(int s, int e, long long w) {
    start = s;
    end = e;
    len = w;
}

vector<Rib> ribs;

void checkNeg() {
    int last = -1;
    for (int i = 0; i < n; i++) {
        last = -1;
        for (auto rib: ribs) {
            if (dist[rib.end] > dist[rib.start] + rib.len) {
                dist[rib.end] = max(-10000000000, dist[rib.start] + rib.len);
                p[rib.end] = rib.start;
                last = rib.end;
            }
        }
    }
    if (last == -1) {
        cout << "NO\n";
    } else {
        int v = last;
        for (int i = 0; i < n; i++) {
            v = p[v];
        }
        vector<int> cycle;
        for (int cur = v;; cur = p[cur]) {
            cycle.push_back(cur);
            if (cur == v && cycle.size() > 1) {
                break;
            }
        }
        cout << "YES\n";
        cout << cycle.size() - 1 << "\n";
        reverse(cycle.begin(), cycle.end());
        for (int i = 1; i < cycle.size(); i++) {
            cout << cycle[i] + 1 << " ";
        }
    }
}

int main() {
    cin >> n;
    dist.assign(n, 10000000000);
    p.assign(n, -1);

    dist[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (w < 100000) {
                ribs.push_back(*(new Rib(i, j, w)));
            }
        }
    }
    checkNeg();
}
