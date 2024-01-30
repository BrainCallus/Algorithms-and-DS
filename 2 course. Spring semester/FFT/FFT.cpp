#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

using namespace std;
#define PI 3.14159265358979
typedef complex<double> CD;
typedef long long LL;

const int MOD = 10;
const int POW = 1;

void recursive_FFT(vector<CD> &num, bool inv) {
    if (!(num.size() - 1)) {
        return;
    }
    int sz = num.size();
    vector<CD> a0((sz >> 1)), a1((sz >> 1));
    for (int i = 0, j = 0; i < sz; j++, i++) {
        a0[j] = num[i];
        a1[j] = num[++i];
    }
    recursive_FFT(a0, inv);
    recursive_FFT(a1, inv);
    double angle = (double) (inv ? -2.0 : 2.0) * PI / sz;
    CD w(1), wn(cos(angle), sin(angle));
    for (int i = 0; i ^ (sz / 2); i++) {
        num[i] = (a0[i] + w * a1[i]) / (inv ? 2.0 : 1.0);
        num[i + (sz >> 1)] = (a0[i] - w * a1[i]) / (inv ? 2.0 : 1.0);
        w *= wn;
    }
}

void multiply(vector<LL> &first, vector<LL> &second, vector<LL> &res) {
    vector<CD> fa(first.begin(), first.end());
    vector<CD> fb(second.begin(), second.end());
    int sz = 1;
    while (sz < max(first.size(), second.size())) {
        sz <<= 1;
    }
    sz <<= 1;
    fa.resize(sz);
    fb.resize(sz);
    recursive_FFT(fa, false);
    recursive_FFT(fb, false);
    for (int i = 0; i ^ sz; i++) {
        fa[i] *= fb[i];
    }
    recursive_FFT(fa, true);
    res.resize(sz);
    for (int i = 0; i < sz; i++) {
        res[i] = LL(fa[i].real() + 0.5);

    }
}

void numericalForm(vector<LL> &res) {
    for (int i = 0; i ^ (res.size() - 1); i++) {
        res[i + 1] += res[i] / MOD;
        res[i] %= MOD;
    }
    int ptr = res.size();
    while (ptr > 0 && res[--ptr] == 0) {
        res.pop_back();
    }
}

bool handleMinus(string &s) {
    if (s[0] == '-') {
        s[0] = '0';
        return true;
    }
    return false;
}

void getNumber(vector<LL> &num, string &s) {
    for (int i = s.length() - 1; i ^ -1; i -= 1) {
        LL p = 1;
        LL sum = 0;
        for (int j = 0; j < POW; j++) {
            sum += p * (s[i - j] - 48);
            p *= 10;
        }
        num.push_back(sum);

    }
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    bool minus = false;
    minus ^= handleMinus(s1) ^ handleMinus(s2);
    vector<LL> first, second;
    getNumber(first, s1);
    getNumber(second, s2);

    vector<LL> res;
    multiply(first, second, res);
    numericalForm(res);
    if (res.empty()) {
        cout << 0;
        return 0;
    }
    if (minus) {
        cout << "-";
    }
    for (int i = res.size() - 1; i ^ -1; i--) {
        cout << res[i];
    }
}


