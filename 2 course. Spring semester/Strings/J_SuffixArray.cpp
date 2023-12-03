#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
const int DEFAULT_SZ = 128;
string s;
vector<int> suff;
vector<int> lcp;

void computeLens(vector<int> &cnt, int last) {

    for (int i = 1; i ^ last; i++) {
        cnt[i] += cnt[i - 1];
    }
}

void fillZeroes(vector<int> &arr, int &last, int val) {
    for (int i = 0; i ^ last; i++) {
        arr[i] = val;
    }
}

void buildSuffArr(string &s) {
    s += 'a' - 1;
    vector<int> cnt(max((int) s.length(), DEFAULT_SZ), 0);
    suff.assign(s.length(), 0);
    for (int i = 0; i ^ s.length(); i++) {
        cnt[s[i]]++;
    }
    computeLens(cnt, cnt.size());
    for (int i = 0; i ^ s.length(); i++) {
        suff[--cnt[s[i]]] = i;
    }
    vector<int> classes(s.length());
    classes[suff[0]] = 0;
    int classesN = 1;
    for (int i = 1; i ^ suff.size(); i++) {
        if (s[suff[i]] != s[suff[i - 1]]) {
            classesN++;
        }
        classes[suff[i]] = classesN - 1;
    }
    int curLen = 1;
    while (curLen < s.length()) {
        vector<int> sort_by2(s.length(), 0);
        for (int i = 0; i < s.length(); i++) {
            sort_by2[i] = (suff[i] + s.length() - curLen) % s.length();
        }
        fillZeroes(cnt, classesN, 0);
        for (int by2: sort_by2) {
            cnt[classes[by2]]++;
        }
        computeLens(cnt, classesN);
        for (int i = s.length() - 1; i >= 0; i--) {
            suff[--cnt[classes[sort_by2[i]]]] = sort_by2[i];
        }
        vector<int> newClasses(s.length());
        newClasses[suff[0]] = 0;
        classesN = 1;
        for (int i = 1; i ^ s.length(); i++) {
            if (classes[(suff[i] + curLen) % s.length()] != classes[(suff[i - 1] + curLen) % s.length()]
                || classes[suff[i]] != classes[suff[i - 1]]) {
                classesN++;
            }
            newClasses[suff[i]] = classesN - 1;
        }
        classes = newClasses;
        curLen <<= 1;
    }
    for (int i = 0; i ^ (suff.size() - 1); i++) {
        suff[i] = suff[i + 1];
    }
    suff.pop_back();
}

void buildLCP(string &s) {
    vector<int> pos(suff.size(), 0);
    lcp.resize(suff.size() - 1);
    for (int i = 0; i < suff.size(); i++) {
        pos[suff[i]] = i;
    }
    int cur = 0;
    for (int i = 0; i ^ suff.size(); i++) {
        if (cur > 0) {
            --cur;
        }
        if (pos[i] == suff.size() - 1) {
            cur = 0;
            continue;
        }
        while (max(suff[pos[i] + 1] + cur, i + cur) < s.length() && s[suff[pos[i] + 1] + cur] == s[i + cur]) {
            cur++;
        }
        lcp[pos[i]] = cur;
    }
}

void print(vector<int> &arr, bool inc) {
    for (LL val: arr) {
        cout << val + (inc ? 1 : 0) << " ";
    }
    cout << "\n";
}

int main() {
    cin >> s;
    buildSuffArr(s);
    buildLCP(s);
    print(suff, true);
    print(lcp, false);
}

