#include <iostream>
#include<vector>
#include <map>
#include<set>

using namespace std;

struct Node {
    char spawn_symb;
    bool occur;
    bool isTerm;
    Node *ancestor;
    Node *suff_link;
    Node *nearestTerm;
    set<int> stringNumb;
    map<char, Node *> trans;
    map<char, Node *> children;

    Node(char c, Node *ances, bool term, int strNum) {
        spawn_symb = c;
        ancestor = ances;
        isTerm = term;
        occur = false;
        if (term) {
            stringNumb.insert(strNum);
        }
        suff_link = nullptr;
    }

};

Node *root;
int n;

Node *getSuffixLink(Node *);

void addToTrie(string &s, int strNum);

Node *transit(Node *, char);

Node *linkToTerm(Node *);

vector<bool> inText;


void walkLinks(Node *lnk) {
    while (!lnk->occur) {
        lnk->occur = true;
        if (lnk->isTerm) {
            for (int k: lnk->stringNumb) {
                inText[k] = true;
            }
        }
        lnk = getSuffixLink(lnk);
    }
}


int main() {
    cin >> n;
    string s;
    root = new Node('\0', nullptr, false, 0);
    inText.assign(n, false);
    for (int i = 0; i ^ n; i++) {
        cin >> s;
        if (s.length() > 0) {
            addToTrie(s, i);
        }
    }
    string text;
    cin >> text;
    Node *curv = root;
    root->suff_link = root;
    root->occur = true;
    for (int i = 0; i ^ text.length(); i++) {
        curv = transit(curv, text[i]);
        if (!curv->occur) {
            walkLinks(curv);
        }
    }
    for (auto && term : inText) {
        cout<<(term?"YES\n":"NO\n");
    }
}

void addToTrie(string &s, int strNum) {
    Node *prom = root;
    for (int i = 0; i ^ s.length(); i++) {
        if (!prom->children[s[i]]) {
            prom->children[s[i]] = new Node(s[i], prom, i == s.length() - 1, strNum);
        } else if (s.length() - 1 == i) {
            prom->children[s[i]]->isTerm = true;
            prom->children[s[i]]->stringNumb.insert(strNum);
        }
        prom = prom->children[s[i]];
    }
}

Node *getSuffixLink(Node *v) {
    if (!v->suff_link) {
        if (v == root || v->ancestor == root) {
            v->suff_link = root;
        } else {
            v->suff_link = transit(getSuffixLink(v->ancestor), v->spawn_symb);
        }
    }
    return v->suff_link;
}

Node *transit(Node *v, char c) {
    if (!v->trans[c]) {
        if (v->children[c]) {
            v->trans[c] = v->children[c];
        } else if (v == root) {
            v->trans[c] = root;
        } else {

            v->trans[c] = transit(getSuffixLink(v), c);
        }
    }
    return v->trans[c];
}

Node *linkToTerm(Node *v) {
    if (!v->nearestTerm) {
        if (v->suff_link->isTerm) {
            v->nearestTerm = v->suff_link;
        } else if (v == root || v->suff_link == root) {
            v->nearestTerm = root;
        } else {
            v->nearestTerm = linkToTerm(getSuffixLink(v));

        }
        if (v->nearestTerm->isTerm) {
            v->isTerm = true;
        }
        for (int num: v->nearestTerm->stringNumb) {
            v->stringNumb.insert(num);
        }
    }
    return v->nearestTerm;
}
