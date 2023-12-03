#include<iostream>
#include<vector>

using namespace std;

vector<int> zFunc;

static void buildPref(string &s) {
    zFunc.assign(s.length(), 0);
    for (int i = 1; i < s.length(); i++) {
        int prev = zFunc[i - 1];
        while (prev > 0 && s[i] != s[prev]) {
            prev = zFunc[prev - 1];
        }
        if (s[i] == s[prev]) {
            prev++;
        }
        zFunc[i] = prev;
    }
}

int main() {
    string s;
    cin >> s;
    buildZF(s);
    for (int i : zFunc) {
        cout << i << " ";
    }

}