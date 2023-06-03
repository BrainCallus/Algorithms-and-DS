#include<iostream>
#include<vector>

using namespace std;

static int n, k;
vector<long> arr;

static long binSearch(int val) {
    int l = -1, r = arr.size(), rightBound;
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (arr[m] > val) {
            r = m;
        } else {
            l = m;
        }
    }
    rightBound = l;
    if (rightBound == -1) return arr[0];

    l = -1;
    r = arr.size();
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (arr[m] >= val) {
            r = m;
        } else {
            l = m;
        }
    }
    if (r == n) return arr[n - 1];
    if (arr[r] - val == val - arr[rightBound]) {
        return arr[rightBound];
    } else if (arr[r] - val <= val - arr[rightBound])
        return arr[r];

    return arr[rightBound];
}


int main() {
    cin >> n >> k;
    arr.resize(n);

    for (int i = 0; i ^ n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i ^ k; i++) {
        int c;
        cin >> c;
        cout << binSearch(c) << "\n";
    }
}
