#include<iostream>
#include<vector>

using namespace std;

vector<int> neprefFunc;
vector<int> entry;

void buildZF(string &s, int m) {
    neprefFunc.assign(s.length(), 0);
    int left = 0, right = 0;
    for (int i = 1; i < s.length(); i++) {
        neprefFunc[i] = max(0, min(right - i, neprefFunc[i - left]));
        while (i + neprefFunc[i] < s.length() && s[neprefFunc[i]] == s[i + neprefFunc[i]]) {
            neprefFunc[i]++;
        }
        if (neprefFunc[i] + i > right) {
            left = i;
            right = i + neprefFunc[i];
        }
        if (i >= m + 1 && neprefFunc[i] == m) {
            entry.push_back(i - m);
        }
    }
    cout << entry.size() << "\n";
    for (int i : entry) {
        cout << i << " ";
    }
}


int main() {
    string s, p;
    cin >> p;
    cin >> s;
    s = p + "#" + s;
    buildZF(s, p.length());
}