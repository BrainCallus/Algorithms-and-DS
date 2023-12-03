#include <iostream>
#include<vector>
#include <map>
#include<set>

using namespace std;

struct Node {
    int pos;
    int firstPos;
    int lastPos;
    bool isTerm;
    char spawn_symb;
    Node *ancestor;
    Node *suff_link;
    Node *link_naspidah;
    set<Node *> linkRev;
    vector<Node *> trans;
    vector<Node *> children;

    Node(char c, Node *ances, bool term, int pos) {
        spawn_symb = c;
        ancestor = ances;
        isTerm = term;
        this->pos = pos;
        firstPos = lastPos = -1;
        suff_link = nullptr;
        link_naspidah = nullptr;
        trans.assign(26, nullptr);
        children.assign(26, nullptr);
    }
};

Node *root;
int n;

Node *getSuffixLink(Node *);

void addToTrie(string &s);

Node *transit(Node *, char &);

Node *linkToTerm(Node *);

vector<Node *> terms;


void walkLinks(Node *&lnk, int firstP, int lastP) {
    while (lnk != root) {
        lnk = getSuffixLink(lnk);
        if ((lnk->firstPos > firstP || lnk->firstPos == -1) && firstP != -1) {
            lnk->firstPos = firstP;
        }
        if (lnk->lastPos < lastP) {
            lnk->lastPos = lastP;
        }
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
        walkLinks(cur, cur->firstPos, cur->lastPos);
    }
}


int main() {
    cin >> n;
    string s;
    root = new Node('\0', nullptr, false, -1);
    for (int i = 0; i ^ n; i++) {
        cin >> s;
        addToTrie(s);
    }
    string text;
    cin >> text;
    Node *curv = root;
    root->suff_link = root;
    for (int i = 0; i ^ text.length(); i++) {
        curv = transit(curv, text[i]);
        getSuffixLink(curv);
        if (curv->firstPos == -1) {
            curv->firstPos = i;
        }
        curv->lastPos = i;
    }
    bfs();
    for (int i = 0; i ^ terms.size(); i++) {
        if (terms[i]->firstPos != -1) {
            cout << terms[i]->firstPos - terms[i]->pos << " " << terms[i]->lastPos - terms[i]->pos << "\n";
        } else {
            cout << -1 << " " << -1 << "\n";
        }
    }
}

void addToTrie(string &s) {

    Node *prom = root;
    for (int i = 0; i ^ s.length(); i++) {
        if (!prom->children[s[i] - 'a']) {
            prom->children[s[i] - 'a'] = new Node(s[i], prom, i == s.length() - 1, i);
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

