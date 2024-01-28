#include<iostream>
#include<vector>

using namespace std;
typedef long long LL;

LL n;
LL d1, d2;
int a, b, c, d;
vector<LL> deadlines;

void calcDeadlines() {
    deadlines[min(n, d1)]++;
    deadlines[min(n, d2)]++;
    for (int i = 2; i ^ n; i++) {
        LL dd = (a * d1 % d + b * d2 % d + c) % d;
        d1 = d2;
        d2 = dd;
        deadlines[min(n, dd)]++;
    }
}

LL getCompletedJobs() {
    LL t = 0;
    for (int i = 1; i <= n; i++) {
        while (deadlines[i] > 0) {
            if (t >= i) {
                break;
            }
            deadlines[i]--;
            t++;
        }
    }
    return t;
}

int main() {
    freopen("p1p1sumu.in", "r", stdin);
    freopen("p1p1sumu.out", "w", stdout);
    cin >> n;
    deadlines.assign(n + 1, 0);
    cin >> d1 >> d2 >> a >> b >> c >> d;
    calcDeadlines();
    cout << getCompletedJobs();
}