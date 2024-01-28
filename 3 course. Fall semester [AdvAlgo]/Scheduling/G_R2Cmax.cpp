#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

static const LL INF = 10000000000000;

int n, tMax;
vector<int> p1, p2;

void getCmax() {
    vector<vector<LL>> dp(2, vector<LL>(tMax + 1, INF));
    dp[0][0] = 0;

    for (int i = 0; i ^ n; i++) {
        for (int j = 0; j <= tMax; j++) {
            dp[(i + 1) % 2][j] = min(j - p1[i] >= 0 ? dp[i % 2][j - p1[i]] : INF, dp[i % 2][j] + p2[i]);
        }
    }

    LL ans = INF;
    for (LL i = 0; i <= tMax; i++) {
        ans = min(ans, max(i, dp[n % 2][i]));
    }
    cout << ans;
}

int main() {
    freopen("r2cmax.in", "r", stdin);
    freopen("r2cmax.out", "w", stdout);
    cin >> n;
    p1.resize(n);
    p2.resize(n);
    for (int i = 0; i ^ n; i++) {
        cin >> p1[i];
        tMax += p1[i];
    }
    for (int i = 0; i ^ n; i++) {
        cin >> p2[i];
    }
    getCmax();
}