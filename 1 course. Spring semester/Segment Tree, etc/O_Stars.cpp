#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

vector<vector<vector<LL>>> fenv;
int n;

void initFenv() {
    fenv.resize(n);
    for (int i = 0; i < n; i++) {
        fenv[i].resize(n);
        for (int j = 0; j < n; j++) {
            fenv[i][j].assign(n, 0);
        }
    }
}

void modify(int &qx, int &qy, int &qz, int &delta) {
    for (int x = qx; x < n; x |= (x + 1)) {
        for (int y = qy; y < n; y |= (y + 1)) {
            for (int z = qz; z < n; z |= (z + 1)) {
                fenv[x][y][z] += delta;
            }
        }
    }
}

int magic(int i) {
    return i & (i + 1);
}

LL getStars(int qx, int qy, int qz) {
    LL stars = 0;
    int x = qx;
    while (x >= 0) {
        int y = qy;
        while (y >= 0) {
            int z = qz;
            while (z >= 0) {
                stars += fenv[x][y][z];
                z = magic(z) - 1;
            }
            y = magic(y) - 1;
        }
        x = magic(x) - 1;
    }
    return stars;
}

LL countSegment(int &xl, int &xr, int &yl, int &yr, int &zl, int &zr) {
    return getStars(xr, yr, zr) - getStars(xr, yl - 1, zr)
           - getStars(xl - 1, yr, zr) + getStars(xl - 1, yl - 1, zr)
           - getStars(xr, yr, zl - 1) + getStars(xr, yl - 1, zl - 1)
           + getStars(xl - 1, yr, zl - 1) - getStars(xl - 1, yl - 1, zl - 1);
}

int main() {
    cin >> n;
    initFenv();
    int query = 0;
    while (true) {
        cin >> query;
        if (query == 1) {
            int x, y, z, delt;
            cin >> x >> y >> z >> delt;
            modify(x, y, z, delt);
        } else if (query == 2) {
            int xl, yl, zl, xr, yr, zr;
            cin >> xl >> yl >> zl >> xr >> yr >> zr;
            cout << countSegment(xl, xr, yl, yr, zl, zr) << "\n";
        } else {
            break;
        }
    }
}
