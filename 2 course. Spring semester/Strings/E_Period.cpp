#include<iostream>
#include<vector>

using namespace std;

vector<int> neprefFunc;

void buildNePref(string &s) {
    neprefFunc.assign(s.length(), 0);
    int left = 0, right = 0;
    for (int i = 1; i ^ s.length(); i++) {
        neprefFunc[i] = max(0, min(right - i, neprefFunc[i - left]));
        while (i + neprefFunc[i] < s.length() && s[neprefFunc[i]] == s[i + neprefFunc[i]]) {
            neprefFunc[i]++;
        }
        if (neprefFunc[i] + i > right) {
            left = i;
            right = i + neprefFunc[i];
        }
    }
}

int getPeriod(string s) {
    buildNePref(s);
    int cyc = s.length();
    for (int i = s.length() - 1; i >= 0; i--) {
        if (neprefFunc[i] == s.length() - i && !(s.length() % i)) {
            cyc = i;
        }
    }
    return cyc;
}

int main() {
    string s;
    cin >> s;
    cout << getPeriod(s);
}