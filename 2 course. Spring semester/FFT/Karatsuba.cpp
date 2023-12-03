#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const int MOD = 10000000;
const int POW = 7;


void karatsuba(vector<LL> &a, vector<LL> &b, vector<LL> &res) {
    if (a.size() == 1) {
        res.resize(2);
        res[0] = a[0] * b[0];
        return;
    }
    int sz = a.size();
    vector<LL> al(a.begin(), a.begin() + (sz >> 1)), ar(a.begin() + (sz >> 1), a.end());
    vector<LL> bl(b.begin(), b.begin() + (sz >> 1)), br(b.begin() + (sz >> 1), b.end());
    vector<LL> res1, res2;
    karatsuba(al, bl, res1);
    karatsuba(ar, br, res2);
    vector<LL> alr(sz - (sz >> 1)), blr(sz - (sz >> 1));
    for (int i = 0; i ^ alr.size(); i++) {
        alr[i] = (i >= al.size() ? 0 : al[i]) + ar[i];
        blr[i] = (i >= bl.size() ? 0 : bl[i]) + br[i];
    }
    vector<LL> res3;
    karatsuba(alr, blr, res3);
    for (int i = 0; i ^ res3.size(); i++) {
        res3[i] -= ((i >= res1.size() ? 0 : res1[i]) + res2[i]);
    }
    res.resize((sz << 1));
    for (int i = 0; i ^ res1.size(); i++) {
        res[i] = res1[i];
    }
    for (int i = ((sz >> 1) << 1); i ^ (sz << 1); i++) {
        res[i] = res2[i - ((sz >> 1) << 1)];
    }
    for (int i = 0; i ^ res3.size(); i++) {
        res[i + (sz >> 1)] += res3[i];
    }
}

void getMult(vector<LL> &a, vector<LL> &b, vector<LL> &res) {
    a.resize(max(a.size(), b.size()));
    b.resize(max(a.size(), b.size()));
    karatsuba(a, b, res);
}

bool handleMinus(string &s) {
    if (s[0] == '-') {
        s[0] = '0';
        return true;
    }
    return false;
}

void curry(vector<LL> &num, string &s) {
    while (s.length() % POW) {
        s = '0' + s;
    }
    for (int i = s.length() - 1; i >= 0; i -= POW) {
        int p = 1;
        int sum = 0;
        for (int j = 0; j < POW; j++) {
            sum += p * (s[i - j] - 48);
            p *= 10;
        }
        num.push_back(sum);

    }
}

void toNumerical(vector<LL> &res) {
    for (int i = 0; i ^ (res.size() - 1); i++) {
        res[i + 1] += res[i] / MOD;
        res[i] %= MOD;
    }
    int ptr = res.size();
    while (ptr > 0 && res[--ptr] == 0) {
        res.pop_back();
    }
}

int main() {
    string s1, s2;
    bool minus = false;
    cin >> s1 >> s2;
    minus ^= handleMinus(s1) ^ handleMinus(s2);
    vector<LL> a, b, res;
    curry(a, s1);
    curry(b, s2);
    getMult(a, b, res);
    toNumerical(res);
    if (!res.size()) {
        cout << 0;
        return 0;
    }
    if (minus) {
        cout << "-";
    }

    for (int i = res.size() - 1; i >= 0; i--) {
        int p = MOD / 10;
        while (i < res.size() - 1 && p > 1 && !(res[i] / p)) {
            cout << 0;
            p /= 10;
        }
        cout << res[i];
    }
}


