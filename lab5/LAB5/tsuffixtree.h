#ifndef TSUFFIXTREE_H
#define TSUFFIXTREE_H
#include <bits/stdc++.h>

const int LEAF_LENGTH = 10e8;

class TNode {
public:
    std::map<char, TNode *> children;

    TNode *parent;
    TNode *suffixLink;

    std::size_t first;
    std::size_t length;

    TNode();
    TNode(const std::string &, TNode *&node, std::size_t &pos);

    ~TNode();
};

class TSuffixTree {
    std::string str;
    TNode *root;
    TNode *activeEdge;
    std::size_t activeLength;
    std::size_t reminder;

    void DeepFirstSearch(TNode *, std::vector<std::size_t> &, std::size_t &total);
public:
    TSuffixTree();

    void Build(const std::string &str);
    void Insert(char c);
    void Find(const std::string &pattern, std::vector<std::size_t> &result);

    ~TSuffixTree();
};

#endif //TSUFFIXTREE_H
