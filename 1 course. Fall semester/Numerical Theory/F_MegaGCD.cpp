#include <iostream>

using namespace std;

void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

int gcd(int a, int b) {
    if (a < b) {
        swap(a, b);
    }
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    cin >> n;
    int num, nod;
    cin >> nod;
    for (int i = 1; i < n; i++) {
        cin >> num;
        nod = gcd(nod, num);
    }
    cout << nod;
}