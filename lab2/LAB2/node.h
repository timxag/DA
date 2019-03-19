/*Created by TimXag 12.01.2019*/

#ifndef TNODE
#define TNODE

typedef struct TNode TNode;

struct TNode
{
    TNode* _left;
    TNode* _right;
    TNode* _parent;
    char* _key;
    unsigned long long int _number;
    short _balance;
};

#endif // TNODE

