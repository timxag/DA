#ifndef TAVL_TREE
#define TAVL_TREE
#include "node.h"
#include <stdbool.h>
class TAvlTree
{
public:
    
    TAvlTree();
    ~TAvlTree();
    int Height(TNode*);
    int CountBalance(TNode*);

    bool Insert(unsigned long long int, char*, TNode**, TNode**, size_t);
    bool Search(char* str, TNode**, size_t);
    bool Remove(char*, TNode**, size_t);

    void SimpleLeftRotate(TNode*);
    void SimpleRightRotate(TNode*);
    void SimpleDelete(TNode*);

    void LeftRotation(TNode*);
    void RightRotation(TNode*);
    void BigLeftRotation(TNode*);
    void BigRightRotation(TNode*);

    void RecountBalanceInsert(TNode*, bool);
    void RecountBalanceDelete(TNode*, bool);

    void LkpLoad(TNode**, TNode*, FILE*);
    void LkpSave(TNode*, FILE*);
    void UpdateRoot();
    TNode* Root;
private:
};
#endif // TAVL_TREE

