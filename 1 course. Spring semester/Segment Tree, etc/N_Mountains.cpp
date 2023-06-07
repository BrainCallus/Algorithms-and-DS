#include <iostream>
#include<vector>

using namespace std;
const int INF = 1000000001;

struct Node {
    int lim;
    int dist;
    int fSet;
    int childPtr;

    Node() {
        lim = 0;
        dist = 0;
        fSet = INF;
        childPtr = -1;
    }

    void refreshDists(vector<Node *> &nodes) {
        lim = max(nodes[childPtr]->lim, nodes[childPtr + 1]->lim + nodes[childPtr]->dist);
        dist = nodes[childPtr]->dist + nodes[childPtr + 1]->dist;
    }

    void breed(vector<Node *> &nodes) {
        if (childPtr == -1) {
            childPtr = nodes.size();
            nodes.push_back(new Node());
            nodes.push_back(new Node());
        }
    }
};

vector<Node *> nodes;

void delegate(int &childPtr, int &flag) {
    nodes[childPtr]->fSet = flag;
    nodes[childPtr + 1]->fSet = flag;
}

void propagate(Node *boss, int vl, int vr) {
    boss->breed(nodes);
    if (boss->fSet == INF) {
        return;
    }
    boss->dist = boss->fSet * (1 + vr - vl);
    boss->lim = boss->dist;
    if (vr - vl > 0) {
        delegate(boss->childPtr, boss->fSet);
    }
    boss->fSet = INF;
}

void modify(int val, int ql, int qr, Node *versh, int vl, int vr) {
    propagate(versh, vl, vr);
    if (qr < vl || ql > vr) {
        return;
    }
    if (ql <= vl && qr >= vr) {
        versh->fSet = val;
        propagate(versh, vl, vr);
        return;
    }
    int vm = vl + ((vr - vl) >> 1);
    modify(val, ql, qr, nodes[versh->childPtr], vl, vm);
    modify(val, ql, qr, nodes[versh->childPtr + 1], vm + 1, vr);
    versh->refreshDists(nodes);
}

int countDist(int h, Node *versh, int vl, int vr) {
    propagate(versh, vl, vr);
    if (vr - vl == 0) {
        return vl;
    }
    int vm = vl + ((vr - vl) >> 1);
    propagate(nodes[versh->childPtr], vl, vm);
    if (nodes[versh->childPtr]->lim > h) {
        return countDist(h, nodes[versh->childPtr], vl, vm);
    }
    propagate(nodes[versh->childPtr + 1], vm + 1, vr);
    return countDist(h - nodes[versh->childPtr]->dist, nodes[versh->childPtr + 1], vm + 1, vr);
}

int main() {
    int n;
    cin >> n;
    nodes.push_back(new Node());
    char oper;
    while (true) {
        cin >> oper;
        if (oper == 'I') {
            int a, b, d;
            cin >> a >> b >> d;
            modify(d, --a, --b, nodes[0], 0, n);
        } else if (oper == 'Q') {
            int h;
            cin >> h;
            cout << countDist(h, nodes[0], 0, n) << "\n";
        } else if (oper == 'E') {
            break;
        }
    }
}



