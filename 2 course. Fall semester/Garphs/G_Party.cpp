#include<iostream>
#include<vector>
#include<stack>

using namespace std;


vector<vector<int>> bonds;
vector<vector<int>> bondsAnti;
vector<bool> mark;
stack<int> list;
vector<int> comp;
int n = 0, m = 0;


class Friend {
public:
    string name;
    int vershNum;
    bool isInvited;

    Friend(string nam = "", int v = -1, bool i = false);

    string getNam();

    int getVershNum();

    void setInvited(bool);

    bool Invited();
};

Friend::Friend(string nam, int v, bool i) {
    name = nam;
    vershNum = v;
    isInvited = i;
}

string Friend::getNam() {
    return name;
}

int Friend::getVershNum() {
    return vershNum;
}

void Friend::setInvited(bool invited) {
    isInvited = invited;
}

bool Friend::Invited() {
    return isInvited;
}

vector<Friend> FRIENDS;

vector<bool> fillFalse(vector<bool> ar) {
    for (auto &&i: ar) {
        i = false;
    }
    return ar;
}

bool equals(string s1, string s2) {
    int len;
    bool flag = true;
    if (s1.length() < s2.length()) len = s1.length();
    else len = s2.length();
    if (s1.length() != s2.length()) flag = false;
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) flag = false;
    }
    return flag;
}

Friend getByName(string &name) {
    for (int i = 0; i < 2 * n + 1; i++) {
        if (equals(FRIENDS[i].getNam(), name)) return FRIENDS[i];
    }
}

void dfs(int v) {
    mark[v] = true;
    for (int u: bonds[v]) {
        if (!mark[u]) {
            dfs(u);
        }
    }
    list.push(v);
}

void dfsCheck(int v, int c) {
    comp[v] = c;
    for (int u: bondsAnti[v]) {
        if (comp[u] == -1) {
            dfsCheck(u, c);
        }
    }
}


void countRibs() {
    for (int i = 0; i < 2 * n; i++) {
        if (!mark[i])
            dfs(i);
    }
    comp.assign(2 * n, -1);
    int c = 0;

    while (!list.empty()) {
        int v = list.top();
        list.pop();
        if (comp[v] == -1) {

            dfsCheck(v, c++);
        }
    }
    int amount = 0;
    for (int i = 0; i < 2 * n; i += 2) {

        if (comp[i] == comp[i ^ 1]) {
            cout << -1;
            exit(0);
        } else if (comp[i] > comp[i ^ 1]) {
            FRIENDS[i / 2].setInvited(true);
            amount++;
        }
    }
    cout << amount << "\n";
    for (auto &i: FRIENDS) {
        if (i.Invited()) cout << i.getNam() << "\n";
    }
}

string substring(string s, int beg, int end);

int main() {

    cin >> n >> m;
    bonds.resize(2 * n);
    bondsAnti.resize(2 * n);
    mark.resize(2 * n);
    mark = fillFalse(mark);
    FRIENDS.resize(n);

    for (int i = 0; i < n; i++) {

        string fried;

        cin >> fried;
        FRIENDS[i] = *(new Friend(fried, i, false));
    }
    for (int i = 0; i < m; i++) {
        int versh = 0, child = 0;
        string demand;
        cin >> demand;
        vector<string> parts;
        parts.resize(2);
        parts[0] = demand;
        cin >> demand;
        cin >> demand;
        parts[1] = demand;

        if (parts[0][0] == '+') {
            parts[0] = substring(parts[0], 1, parts[0].size());
            versh = 2 * getByName(parts[0]).getVershNum();
        } else {
            parts[0] = substring(parts[0], 1, parts[0].size());
            versh = 2 * getByName(parts[0]).getVershNum() + 1;
        }

        if (parts[1][0] == '+') {
            parts[1] = substring(parts[1], 1, parts[1].size());
            child = 2 * getByName(parts[1]).getVershNum();
        } else {
            parts[1] = substring(parts[1], 1, parts[1].size());
            child = 2 * getByName(parts[1]).getVershNum() + 1;
        }
        bonds[versh].push_back(child);
        bonds[child ^ 1].push_back(versh ^ 1);

        bondsAnti[child].push_back(versh);
        bondsAnti[versh ^ 1].push_back(child ^ 1);

    }
    countRibs();
}


string substring(string s, int beg, int end) {
    string sub;
    for (int i = beg; i < end; i++) {
        sub += s[i];
    }
    return sub;
}

