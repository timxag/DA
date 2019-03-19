#include "tsuffixtree.h"

TNode::TNode() {
    parent = suffixLink = nullptr;
    first = length = 0;
}

TNode::TNode(const std::string &str, TNode *&node, std::size_t &pos){
    children[str[node->first + pos]] = node;
    parent = node->parent;
    suffixLink = nullptr;
    first = node->first;
    length = pos;

    TNode *temp = new TNode;
    temp->parent = this;
    temp->first = str.size() - 1;
    temp->length = LEAF_LENGTH;
    children[str[str.size() - 1]] = temp;

    node->parent->children[str[node->first]] = this;
    node->parent = this;
    node->first += pos;

    if (node->length != LEAF_LENGTH) {
        node->length -= pos;
    }
}

TNode::~TNode() {
    for (std::map<char, TNode *>::iterator it = children.begin(); it != children.end(); ++it) {
        delete it->second;
    }
}

TSuffixTree::TSuffixTree() {
    root = new TNode;

    root->suffixLink = new TNode;

    for (char i = 'a'; i <= 'z'; ++i) {
        root->suffixLink->children[i] = root;
    }

    root->suffixLink->children['$'] = root;

    activeEdge = root;
    activeLength = 0;
    reminder = 0;
}

void TSuffixTree::DeepFirstSearch(TNode *cur, std::vector<std::size_t> &result, std::size_t &total) {
    if (cur->children.empty()) {
        result.push_back(str.size() - total);
        return;
    }

    for (std::map<char, TNode *>::const_iterator it = cur->children.begin(); it != cur->children.end(); ++it) {
        std::size_t temp = total;

        if (it->second->length == LEAF_LENGTH) {
            temp += str.size() - it->second->first;
        } else {
            temp += it->second->length;
        }

        DeepFirstSearch(it->second, result, temp);
    }
}

void TSuffixTree::Build(const std::string &str) {
    for (int i = 0; i < str.size(); ++i) {
        Insert(str[i]);
    }

    Insert('$');
}

void TSuffixTree::Insert(char c) {
    str.push_back(c);

    std::map<char, TNode *>::iterator it;
    TNode *last = nullptr;

    while ((activeLength < activeEdge->length && str[activeEdge->first + activeLength] != c) ||
           (activeLength >= activeEdge->length && (it = activeEdge->children.find(c)) == activeEdge->children.end())) {

        if (activeLength < activeEdge->length && str[activeEdge->first + activeLength] != c) {
            TNode *temp = new TNode(str, activeEdge, activeLength);

            if (last) {
                last->suffixLink = temp;
            }

            last = activeEdge->parent;
            activeEdge = last->parent->suffixLink->children[str[reminder]];

            if (activeEdge == root) {
                --activeLength;
                ++reminder;
            }

            for (std::size_t length; activeLength > activeEdge->length; activeLength -= length) {
                length = activeEdge->length;
                reminder += length;
                activeEdge = activeEdge->children[str[reminder]];
            }
        } else {
            TNode *temp = new TNode;
            temp->parent = activeEdge;
            temp->first = str.size() - 1;
            temp->length = LEAF_LENGTH;

            activeEdge->children[str[str.size() - 1]] = temp;

            if (last) {
                last->suffixLink = activeEdge;
                last = nullptr;
            }

            if (activeEdge != root) {
                activeEdge = activeEdge->suffixLink;
                activeLength = activeEdge->length;
            }
        }
    }

    if (last) {
        last->suffixLink = activeEdge;
    }

    if (activeLength >= activeEdge->length && it != activeEdge->children.end() && it->second->first < str.size() - 1) {
        activeLength = 1;
        activeEdge = it->second;
        reminder = activeEdge->first;
    } else {
        ++activeLength;
    }
}


void TSuffixTree::Find(const std::string &pattern, std::vector<std::size_t> &result) {
    if (pattern.size() >= str.size()) {
        return;
    }

    TNode *cur = root;
    std::size_t total = 0;

    for (std::size_t i = 0, j = 0; j < pattern.size(); ++i, ++j) {
        if (i >= cur->length) {
            std::map<char, TNode *>::iterator it = cur->children.find(pattern[j]);

            if (it == cur->children.end()) {
                return;
            }

            cur = it->second;

            if (cur->length == LEAF_LENGTH) {
                total += str.size() - cur->first;
            } else {
                total += cur->length;
            }

            i = 0;
        }

        if (pattern[j] != str[cur->first + i]) {
            return;
        }
    }

    DeepFirstSearch(cur, result, total);

    if (result.size() > 1) {
        std::sort(result.begin(), result.end());
    }
}

TSuffixTree::~TSuffixTree() {
    root->suffixLink->children.clear();
    delete root->suffixLink;
    delete root;
}

