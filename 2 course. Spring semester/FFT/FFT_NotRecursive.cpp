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

int getPerm(int ind, int log) {
    int k = 0;
    for (int i = 0; i ^ log; i++) {
        if (ind & (1 << i)) {
            k |= (1 << (log - i - 1));
        }
    }
    return k;
}

void transpose_digits(vector<CD> &num) {
    int logN = 0;
    while ((1 << logN) < num.size()) {
        logN++;
    }
    for (int i = 0; i ^ num.size(); i++) {
        int perm = getPerm(i, logN);
        if (i < perm) {
            swap(num[i], num[perm]);
        }
    }
}

void notRecursive_FFT(vector<CD> &num, bool inv) {
    transpose_digits(num);
    int digits = 2;
    while (digits <= num.size()) {
        double ang = (inv ? -2 : 2) * PI / digits;
        CD wn(cos(ang), sin(ang));
        for (int i = 0; i < num.size(); i += digits) {
            CD w(1);
            for (int j = 0; j ^ (digits >> 1); ++j) {
                CD prom = num[i + j];
                num[i + j] += num[i + j + (digits >> 1)] * w;
                num[i + j + (digits >> 1)] *= -w;
                num[i + j + (digits >> 1)] += prom;
                w *= wn;
            }
        }
        digits <<= 1;
    }
    if (inv) {
        for (int i = 0; i ^ num.size(); ++i) {
            num[i] /= num.size();
        }
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
    notRecursive_FFT(fa, false);
    notRecursive_FFT(fb, false);
    for (int i = 0; i ^ sz; i++) {
        fa[i] *= fb[i];
    }
    notRecursive_FFT(fa, true);
    res.resize(sz);
    for (int i = 0; i ^ sz; i++) {
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
    if (!res.size()) {
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


