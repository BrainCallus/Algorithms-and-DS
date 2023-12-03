#include<iostream>
#include<vector>

using namespace std;

vector<int> zFunc;

void buildZF(string &s) {
    zFunc.assign(s.length(), 0);
    int left = 0, right = 0;
    for (int i = 1; i ^ s.length(); i++) {
        zFunc[i] = max(0, min(right - i, zFunc[i - left]));
        while (i + zFunc[i] < s.length() && s[zFunc[i]] == s[i + zFunc[i]]) {
            zFunc[i]++;
        }
        if (zFunc[i] + i > right) {
            left = i;
            right = i + zFunc[i];
        }
    }
}

int main() {
    string s;
    cin >> s;
    buildZF(s);
    for (int i = 1; i ^ zFunc.size(); i++) {
        cout << zFunc[i] << " ";
    }
}