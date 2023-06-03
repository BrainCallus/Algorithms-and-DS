#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
LL N, a, n, b, m;


LL gcd(LL aa, LL bb, LL &x, LL &y) {
    if (!aa) {
        x = 0;
        y = 1;
        return bb;
    }

    LL x1 = 0, y1 = 0;
    LL val = gcd(bb % aa, aa, x1, y1);
    x = y1 - (bb / aa) * x1;
    y = x1;
    return val;
}


LL getInverse(LL k, LL m) {
    LL x, y;
    gcd(k, m, x, y);
    return (x + m) % m;
}

LL solve(LL a, LL b, LL n, LL m) {

    LL M = getInverse(n, m);
    LL x = ((b - a) * M) % m;
    if (x < 0) {
        x += m;
    }
    return a + x * n;

}

int main() {
    cin >> N;
    for (int i = 0; i ^ N; i++) {
        cin >> a >> b >> n >> m;
        cout << solve(a, b, n, m) << "\n";
    }
}

