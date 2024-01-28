#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;
int n;
LL cMax;
vector<int> aJob;
vector<int> bJob;

pair<int, int> buildI_J_andFindMax(vector<int> &I, vector<int> &J) {
    int x = -1, y = -1;
    LL sumA = 0, sumB = 0, sumAB = -1;
    for (int i = 0; i < n; i++) {
        sumA += aJob[i];
        sumB += bJob[i];
        if (aJob[i] + bJob[i] > sumAB) {
            sumAB = aJob[i] + bJob[i];
        }
        if (aJob[i] <= bJob[i]) {
            if (!(x + 1) || aJob[i] > aJob[x]) {
                x = i;
            }
            I.push_back(i);
        } else {
            if (!(y + 1) || bJob[i] > bJob[y]) {
                y = i;
            }
            J.push_back(i);
        }
    }
    cMax = max(sumAB, max(sumA, sumB));
    return {x, y};
}


pair<vector<LL>, vector<LL>> bSchedule(int &x, vector<int> &iset, vector<int> &jset, bool swap) {
    vector<LL> schedule1(n), schedule2(n);
    LL t1 = 0, t2 = 0;
    schedule2[x] = 0;
    schedule1[x] = cMax - (swap ? bJob : aJob)[x];
    t2 += (swap ? aJob : bJob)[x];
    for (int i: iset) {
        if (i != x) {
            schedule1[i] = t1;
            schedule2[i] = t2;
            t1 += (swap ? bJob : aJob)[i];
            t2 += (swap ? aJob : bJob)[i];
        }
    }
    t1 = schedule1[x];
    t2 = cMax;
    for (int i = jset.size() - 1; i >= 0; i--) {
        if (jset[i] != x) {
            t1 -= (swap ? bJob : aJob)[jset[i]];
            t2 -= (swap ? aJob : bJob)[jset[i]];
            schedule1[jset[i]] = t1;
            schedule2[jset[i]] = t2;
        }
    }
    if (swap) {
        return {schedule2, schedule1};
    } else {
        return {schedule1, schedule2};
    }
}

void constructSchedule() {
    vector<int> I, J;
    pair<int, int> xy = buildI_J_andFindMax(I, J);
    int x = xy.first, y = xy.second;
    pair<vector<LL>, vector<LL>> scheduleAB;

    if (J.empty() || !I.empty() && aJob[x] >= bJob[y]) {
        scheduleAB = bSchedule(x, I, J, false);
    } else {
        scheduleAB = bSchedule(y, J, I, true);
    }
    cout << cMax << "\n";

    for (LL a: scheduleAB.first) {
        cout << a << " ";
    }
    cout << "\n";
    for (LL b: scheduleAB.second) {
        cout << b << " ";
    }
}

int main() {
    freopen("o2cmax.in", "r", stdin);
    freopen("o2cmax.out", "w", stdout);
    cin >> n;
    aJob.resize(n);
    bJob.resize(n);
    for (int i = 0; i ^ n; i++) {
        cin >> aJob[i];
    }
    for (int i = 0; i ^ n; i++) {
        cin >> bJob[i];
    }
    constructSchedule();
}