#include <iostream>
#include <vector>

using namespace std;

vector<int> divs;

void evaluateDivs(int maxN) {
    divs.assign(maxN + 1, -1);
    for (int i = 0; i < divs.size(); i++) {
        divs[i] = i;
    }
    for (int i = 2; i < divs.size(); i++) {
        if (divs[i] == i) {
            for (int j = i; j <= maxN; j += i) {
                divs[j] = i;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> nums;
    int num, mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num > mx) {
            mx = num;
        }
        nums.push_back(num);
    }
    evaluateDivs(mx);
    for (int i = 0; i < nums.size(); i++) {
        vector<int> d;
        while (nums[i] != 1) {
            d.push_back(divs[nums[i]]);
            nums[i] /= divs[nums[i]];
        }
        for (int j = d.size() - 1; j >= 0; j--) {
            cout << d[j] << " ";
        }
        cout << "\n";
    }
}