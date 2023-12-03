#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

int n, m, r;

struct Matrix {
    LL e_11 = 0;
    LL e_12 = 0;
    LL e_21 = 0;
    LL e_22 = 0;

    Matrix() {
        e_11 = 1;
        e_12 = 0;
        e_21 = 0;
        e_22 = 1;
    }

    Matrix(LL e_11, LL e_12, LL e_21, LL e_22) {
        this->e_11 = e_11;
        this->e_12 = e_12;
        this->e_21 = e_21;
        this->e_22 = e_22;
    }
};

vector<Matrix> arr;
vector<Matrix> tree;

Matrix mult(Matrix &thhis, Matrix &mat) {
    return Matrix(
            (thhis.e_11 * mat.e_11 + thhis.e_12 * mat.e_21) % r,
            (thhis.e_11 * mat.e_12 + thhis.e_12 * mat.e_22) % r,
            (thhis.e_21 * mat.e_11 + thhis.e_22 * mat.e_21) % r,
            (thhis.e_21 * mat.e_12 + thhis.e_22 * mat.e_22) % r
    );
}

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = arr[vl];
        return;
    }
    build(2 * v + 1, vl, vl + (vr - vl) / 2);
    build(2 * v + 2, vl + (vr - vl) / 2, vr);
    tree[v] = mult(tree[2 * v + 1], tree[2 * v + 2]);
}

Matrix getMultiplication(int ql, int qr, int v, int vl, int vr) {
    if (qr <= vl || ql >= vr) {
        return Matrix();
    }
    if (ql <= vl && vr <= qr) {
        return tree[v];
    }
    Matrix m1 = getMultiplication(ql, qr, 2 * v + 1, vl, vl + (vr - vl) / 2);
    Matrix m2 = getMultiplication(ql, qr, 2 * v + 2, vl + (vr - vl) / 2, vr);
    return mult(m1, m2);
}

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    scanf("%d %d %d", &r, &n, &m);
    arr.resize(n);
    tree.resize(n * 4);
    for (int i = 0; i < n; i++) {
        LL e_11, e_12, e_21, e_22;
        scanf("%lld%lld%lld%lld", &e_11, &e_12, &e_21, &e_22);
        arr[i] = Matrix(e_11, e_12, e_21, e_22);
    }
    build(0, 0, n);
    for (int i = 0; i < m; i++) {
        int ql, qr;
        scanf("%d%d", &ql, &qr);
        Matrix mat = getMultiplication(ql - 1, qr, 0, 0, n);
        printf("%lld %lld\n%lld %lld\n\n", mat.e_11, mat.e_12, mat.e_21, mat.e_22);
    }
    return 0;
}

