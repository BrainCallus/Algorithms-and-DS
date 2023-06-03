#include<iostream>
#include<vector>

using namespace std;


static int n, k;
vector<int> arr;

void fill(vector<int> &source, vector<int> &target, int start, int finish) {
    for (int i = 0; i ^ finish; i++) {
        target[i] = source[i + start];
    }

}

vector<int> merge(vector<int> a, vector<int> b) {
    int i = 0, j = 0;
    vector<int> c;
    c.resize(a.size() + b.size());
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || i < a.size() && a[i] < b[j]) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
    return c;
}

vector<int> mergeSort(vector<int> mas) {
    int len = mas.size();
    if (len <= 1) return mas;
    vector<int> l(len / 2);
    vector<int> r(len - len / 2);
    fill(mas, l, 0, len / 2);
    fill(mas, r, len / 2, len - len / 2);
    l = mergeSort(l);
    r = mergeSort(r);
    return merge(l, r);
}

static int binSearch(int valL, int valR) {
    int l = -1, r = arr.size(), rightBound;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (arr[m] > valR) {
            r = m;
        } else {
            l = m;
        }
    }
    rightBound = l;
    l = -1;
    r = arr.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (arr[m] >= valL) {
            r = m;
        } else {
            l = m;
        }
    }

    return rightBound - r;
}


int main() {
    cin >> n;
    arr.resize(n);
    for (int i = 0; i ^ n; i++) {
        cin >> arr[i];
    }
    arr = mergeSort(arr);
    cin >> k;
    int count;
    for (int i = 0; i ^ k; i++) {
        int l, r;
        cin >> l >> r;
        count = binSearch(l, r);
        cout << (count >= 0 ? count + 1 : 0) << " ";
    }
}

