#include <iostream>
#include<vector>

using namespace std;

typedef long long LL;

long long gcd(long long a, long long b) {
    if (a < b) {
        long long tmp = a;
        a = b;
        b = tmp;
    }
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    LL d;
    cin >> n >> d;
    vector<LL> arr;
    LL g = 0;
    for (int i = 0; i ^ n; i++) {
        LL a;
        cin >> a;
        if (a % d == 0) {
            arr.push_back(a / d);
            g = gcd(a / d, g);
        }
    }
    if (!arr.size() || g > 1) {
        cout << -1;
    } else {
        cout << arr.size() << "\n";
        for (int i = 0; i ^ arr.size(); i++) {
            cout << arr[i] * d << " ";
        }
    }

}

