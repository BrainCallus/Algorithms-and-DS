#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums;
    int num;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num > mx) {
            mx = num;
        }
        nums.push_back(num);
    }

    vector<bool> ch;
    ch.assign(mx + 1, true);
    for (int i = 2; i <= mx; i++) {
        if (ch[i]) {
            for (int j = 2; j <= mx / i; j++) {
                ch[i * j] = false;
            }
        }
    }
    for (int i = 0; i < nums.size(); i++) {

        if (ch[nums[i]]) {
            cout << "YES\n";

        } else {
            cout << "NO\n";
        }
    }

}