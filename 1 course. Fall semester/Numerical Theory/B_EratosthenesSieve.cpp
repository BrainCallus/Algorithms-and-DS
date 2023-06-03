#include <iostream>
#include <vector>

using namespace std;

int main() {
    int A, B;
    cin >> A >> B;
    vector<bool> ch;
    ch.assign(B + 1, true);
    vector<long> arr;
    for (int i = 2; i <= B; i++) {
        if (ch[i]) {
            if (i >= A) arr.push_back(i);
            for (int j = 2; j <= B / i; j++) {
                ch[i * j] = false;
            }
        }
    }
    for (long i : arr) {
        cout << i << " ";
    }

}