#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    long long n;
    cin >> n;
    int sz = sqrt(n)+1;
    vector<bool> ch; ch.assign(sz, true);
    vector<long> arr;
    for (int i = 2; i<sz; i++) {
        if (ch[i]) {
            arr.push_back(i);
            for (int j = 2; j < sz / i; j++) {
                ch[i * j] = false;
            }
        }
    }
    for (long i : arr) {
        if (n % i == 0) {
            cout << "False";
            return 0;
        }
    }
    cout << "True";
    return 0;
}
