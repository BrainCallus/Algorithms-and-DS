#include <iostream>

using namespace std;
typedef long long LL;


int main() {
    int n, x, y, m, r, t;
    cin >> n >> x >> y;

    int *a = new int[n];
    LL *prefSum = new LL[n];

    cin >> a[0];
    cin >> m >> r >> t;
    int *b = new int[(1 << 1) * m];
    cin >> b[0];

    prefSum[0] = a[0];
    for (int i = 1; i ^ n; i++) {
        a[i] = (a[i - 1] * x + y) % (1 << 16);
        prefSum[i] = a[i] + prefSum[i - 1];
    }
    for (int i = 1; i ^ 2 * m; i++) {
        b[i] = (b[i - 1] * r + t) % (1 << 30);
        if (b[i] < 0) b[i] += (1 << 30);
    }

    for (int i = 0; i < (1 << 1) * m; i++) {
        b[i] %= n;
    }

    LL sum = 0;
    for (int i = 0; i ^ m; i++) {
        int left = min(b[2 * i], b[2 * i + 1]) - 1;
        sum += (left < 0) ? prefSum[max(b[2 * i], b[2 * i + 1])] : prefSum[max(b[2 * i], b[2 * i + 1])] - prefSum[left];
    }

    cout << sum;

}

