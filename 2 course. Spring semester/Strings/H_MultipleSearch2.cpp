#include <iostream>
#include<vector>
#include <map>
#include<set>

using namespace std;

struct Node {
    char spawn_symb;
    int buf;
    int entries;
    bool isTerm;
    Node *ancestor;
    Node *suff_link;
    Node *link_naspidah;
    set<Node *> linkRev;
    vector<Node *> trans;
    vector<Node *> children;

    Node(char c, Node *ances, bool term) {
        spawn_symb = c;
        ancestor = ances;
        isTerm = term;
        entries = 0;
        buf = 0;
        children.assign(26, nullptr);
        trans.assign(26, nullptr);
        suff_link = nullptr;
        link_naspidah = nullptr;
    }
};

Node *root;

int n;

Node *getSuffixLink(Node *);

void addToTrie(string &s);

Node *transit(Node *, char &);

Node *linkToTerm(Node *);

vector<Node *> terms;


void walkLinks(Node *&lnk, int del) {
    while (lnk != root) {
        lnk = linkToTerm(lnk);
        lnk->buf += del;
    }
}

void bfs() {
    vector<Node *> q;
    for (Node *ch: root->children) {
        if (ch) {
            q.push_back(ch);
        }
    }
    while (!q.empty()) {
        Node *cur = q.back();
        q.pop_back();
        for (Node *child: cur->children) {
            if (child) {
                q.push_back(child);
            }
        }
        walkLinks(cur, cur->entries);
    }
}


int main() {
    cin >> n;
    string s;
    root = new Node('\0', nullptr, false);
    for (int i = 0; i ^ n; i++) {
        cin >> s;
        addToTrie(s);
    }
    string text;
    cin >> text;
    Node *curv = root;
    root->suff_link = root;
    for (char &ch: text) {
        curv = transit(curv, ch);
        getSuffixLink(curv);
        curv->entries++;
    }
    bfs();
    for (auto &term: terms) {
        cout << term->entries + term->buf << "\n";
    }
}

void addToTrie(string &s) {
    Node *prom = root;
    for (int i = 0; i ^ s.length(); i++) {
        if (!prom->children[s[i] - 'a']) {
            prom->children[s[i] - 'a'] = new Node(s[i], prom, i == s.length() - 1);
        }
        if (s.length() - 1 == i) {
            prom->children[s[i] - 'a']->isTerm = true;

        }
        prom = prom->children[s[i] - 'a'];
    }
    terms.push_back(prom);
}

Node *getSuffixLink(Node *v) {
    if (!v->suff_link) {
        if (v == root || v->ancestor == root) {
            v->suff_link = root;
        } else {
            v->suff_link = transit(getSuffixLink(v->ancestor), v->spawn_symb);
        }
        v->suff_link->linkRev.insert(v);
    }
    return v->suff_link;
}

Node *transit(Node *v, char &c) {
    if (!v->trans[c - 'a']) {
        if (v->children[c - 'a']) {
            v->trans[c - 'a'] = v->children[c - 'a'];
        } else if (v == root) {
            v->trans[c - 'a'] = root;
        } else {

            v->trans[c - 'a'] = transit(getSuffixLink(v), c);
        }
    }
    return v->trans[c - 'a'];
}


Node *linkToTerm(Node *v) {
    if (!v->link_naspidah) {
        if (getSuffixLink(v)->isTerm) {
            v->link_naspidah = v->suff_link;
        } else if (v == root || v->suff_link == root) {
            v->link_naspidah = root;
        } else {
            v->link_naspidah = linkToTerm(v->suff_link);
        }
    }
    return v->link_naspidah;
}

