#include <iostream>
#include<vector>

using namespace std;

int M;
int id, logN;

struct Karno {
    int num;
    int depth = -1;
    Karno *ancestor;
    vector<Karno *> tutors;

    Karno(int idx) {
        num = idx;
        ancestor = this;
        tutors.assign(logN + 1, this);
    }

    void assignTutors() {
        for (int i = 1; i <= logN; i++) {
            tutors[i] = tutors[i - 1]->tutors[i - 1];
        }
    }

};

vector<Karno *> dinos;

void precalcLog() {
    logN = 1;
    while ((1 << logN) <= M) {
        logN++;
    }
}


Karno *LCA(int v1, int v2) {
    Karno *v = dinos[v1];
    Karno *u = dinos[v2];
    if (v->depth < u->depth) {
        swap(v, u);
    }

    for (int i = logN - 1; i >= 0; i--) {
        if ((1 << i) <= v->depth - u->depth) {
            v = v->tutors[i];
        }
    }
    if (u == v) {
        return v;
    }
    for (int i = logN - 1; i >= 0; i--) {
        if (v->tutors[i] != u->tutors[i]) {
            v = v->tutors[i];
            u = u->tutors[i];
        }
    }

    return v->tutors[0];
}

void createKarno(Karno *tutor) {
    dinos.push_back(new Karno(++id));
    dinos[id]->depth = tutor->depth + 1;
    dinos[id]->tutors[0] = tutor;
    dinos[id]->assignTutors();
}

Karno *dsu_find(Karno *karno) {
    if (karno != karno->ancestor) {
        karno->ancestor = dsu_find(karno->ancestor);
    }
    return karno->ancestor;
}

void dsu_kill(Karno *x, Karno *y) {
    if (x != y) {
        x->ancestor = y;
        y->ancestor = y;
    }
}

int main() {
    cin >> M;
    precalcLog();
    id = 0;
    dinos.push_back(new Karno(id++));
    dinos.push_back(new Karno(id));
    char q;
    int k, v;
    for (int i = 0; i < M; i++) {
        cin >> q >> k;
        if (q == '?') {
            cin >> v;
            cout << dsu_find(LCA(k, v))->num << "\n";
        } else if (q == '+') {
            createKarno(dinos[k]);
        } else {
            dsu_kill(dsu_find(dinos[k]), dsu_find(dinos[k]->tutors[0]));
        }
    }

}
