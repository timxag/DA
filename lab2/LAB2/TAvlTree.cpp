#include <iostream>
#include <string.h>
#include "node.h"
#include "TAvlTree.h"
#include <stdbool.h>

#ifndef max
    #define max(a,b) (a > b ? a : b)
#endif
using namespace std;

TAvlTree::TAvlTree()
{
    Root = NULL;
}
TAvlTree::~TAvlTree()
{
    SimpleDelete(Root);
}
void TAvlTree::SimpleDelete(TNode* n)
{
    if(n == NULL) return;
    SimpleDelete(n->_left);
    SimpleDelete(n->_right);
    delete[] n->_key;
    delete n;
    n = NULL;
}
void TAvlTree::UpdateRoot()
{
    while(Root->_parent != NULL)
    {
        Root = Root->_parent;
    }
}
int TAvlTree::Height(TNode* node)
{
    if (node == NULL) return 0;
    int left = Height(node->_left);
    int right = Height(node->_right);
    return max(left, right) + 1;
}
int TAvlTree::CountBalance(TNode* node)
{
    if(node == NULL) return 0;
    return Height(node->_left) - Height(node->_right);
}
void TAvlTree::SimpleLeftRotate(TNode* pivot)
{
    TNode* tmp = pivot->_right->_left;
    TNode* parentOfPivot = pivot->_parent;
    if(parentOfPivot != NULL)
    {
        if(parentOfPivot->_left == pivot) parentOfPivot->_left = pivot->_right;
        else parentOfPivot->_right = pivot->_right;
    }
    pivot->_parent = pivot->_right;
    if(tmp != NULL) tmp->_parent = pivot;
    pivot->_right->_parent = parentOfPivot;
    pivot->_right->_left = pivot;
    pivot->_right = tmp;
    UpdateRoot();
}
void TAvlTree::SimpleRightRotate(TNode* pivot)
{
    TNode* tmp = pivot->_left->_right;
    TNode* parentOfPivot = pivot->_parent;
    if(parentOfPivot != NULL)
    {
        if(parentOfPivot->_right == pivot) parentOfPivot->_right = pivot->_left;
        else parentOfPivot->_left = pivot->_left;
    }
    pivot->_parent = pivot->_left;
    if(tmp != NULL) tmp->_parent = pivot;
    pivot->_left->_parent = parentOfPivot;
    pivot->_left->_right = pivot;
    pivot->_left = tmp;
    UpdateRoot();
}
void TAvlTree::LeftRotation(TNode* current)
{
    SimpleLeftRotate(current);
    if(current->_parent->_balance == 0)
    {
        current->_parent->_balance = 1;
        current->_balance = -1;
    }
    else
    {
        current->_parent->_balance = 0;
        current->_balance = 0;
    }
}
void TAvlTree::RightRotation(TNode* current)
{
    // according to balance table
    SimpleRightRotate(current);
    if(current->_parent->_balance == 0)
    {
        current->_parent->_balance = -1;
        current->_balance = 1;
    }
    else
    {
        current->_parent->_balance = 0;
        current->_balance = 0;
    }
}
void TAvlTree::BigLeftRotation(TNode* current)
{
    // according to balance table
    SimpleRightRotate(current->_right);
    SimpleLeftRotate(current);
    if(current->_parent->_balance == 1)
    {
        current->_balance = 0;
        current->_parent->_right->_balance = -1;
    }
    else if(current->_parent->_balance == -1)
    {
        current->_balance = 1;
        current->_parent->_right->_balance = 0;
    }
    else
    {
        current->_balance = 0;
        current->_parent->_right->_balance = 0;
    }
    current->_parent->_balance = 0;
}
void TAvlTree::BigRightRotation(TNode* current)
{
    // according to balance table
    SimpleLeftRotate(current->_left);
    SimpleRightRotate(current);
    if(current->_parent->_balance == 1)
    {
        current->_balance = -1;
        current->_parent->_left->_balance = 0;
    }
    else if(current->_parent->_balance == -1)
    {
        current->_balance = 0;
        current->_parent->_left->_balance = 1;
    }
    else
    {
        current->_balance = 0;
        current->_parent->_left->_balance = 0;
    }
    current->_parent->_balance = 0;
}

void TAvlTree::RecountBalanceInsert(TNode* node, bool src)
{
    if(node == NULL) return;
    if(!src)// left
        node->_balance++;
    else
        node->_balance--;
    if(node->_balance == 0) return;
    if(node->_balance > 1)//==2
    {
        int L = Height(node->_left->_left);
        int R = Height(node->_left->_right);
        if(R > L)
            BigRightRotation(node);
        else
            RightRotation(node);
        node = node->_parent;
    }
    else if(node->_balance < -1)//==-2
    {
        int L = Height(node->_right->_left);
        int R = Height(node->_right->_right);
        if(L > R)
            BigLeftRotation(node);
        else
            LeftRotation(node);
        node = node->_parent;
    }
    if(node->_parent == NULL)return;
    if(node->_balance == 0) return;
    if(node->_parent->_left == node) return RecountBalanceInsert(node->_parent, false);
    else return RecountBalanceInsert(node->_parent, true);
}
void TAvlTree::RecountBalanceDelete(TNode* node, bool src)
{
    if(node == NULL) return;
    if(!src) // from left
        node->_balance--;
    else //from right
        node->_balance++;
    if(node->_balance == 1 || node->_balance == -1) return;
    if(node->_balance > 1) //==2
    {
        int L = Height(node->_left->_left);
        int R = Height(node->_left->_right);
        if(R > L)
            BigRightRotation(node);
        else
            RightRotation(node);
        node = node->_parent;
    }
    else if(node->_balance < -1)//==-2
    {
        int L = Height(node->_right->_left);
        int R = Height(node->_right->_right);
        if(L > R)
            BigLeftRotation(node);
        else
            LeftRotation(node);
        node = node->_parent;
    }
    if(node == NULL) return;
    if(node->_balance == 1 || node->_balance == -1) return;
    if(node->_parent == NULL) return;
    if(node->_parent->_left == node) return RecountBalanceDelete(node->_parent, false);
    else return RecountBalanceDelete(node->_parent, true);
}
bool TAvlTree::Search(char* str,  TNode** node, size_t len)
{
    if((*node) == NULL)
    {
        printf("NoSuchWord\n");
        return false;
    }
    int res = strncmp((*node)->_key, str,len + 1);
    if(res == 0)
    {
        printf("OK: %llu\n",(*node)->_number);
        return true;
    }
    else if(res < 0)
        return Search(str, &((*node)->_left), len);
    else if(res > 0)
        return Search(str, &((*node)->_right), len);
    else return false;
}
bool TAvlTree::Insert(unsigned long long int number, char* str, TNode** node, TNode** parent, size_t len)
{
    if(*node == NULL)
    {
        TNode* tmp = new TNode;
        tmp->_left = NULL;
        tmp->_right = NULL;
        if(parent == NULL) tmp->_parent = NULL;
        else tmp->_parent = *parent;
        tmp->_number = number;

        tmp->_key = new char[len + 1];
        strncpy(tmp->_key, str, len);
        tmp->_key[len] = '\0';

        tmp->_balance = 0;
        *node = tmp;
        if(tmp->_parent != NULL)
        {
            if(tmp->_parent->_left == tmp) RecountBalanceInsert((*node)->_parent, false);
            else RecountBalanceInsert((*node)->_parent, true);
        }
        printf("OK\n");
        return true;
    }
    int res = strncmp((*node)->_key, str, len + 1);
    if(res == 0)
    {
        printf("Exist\n");
        return false;
    }
    else if(res < 0)
        return Insert(number, str, &((*node)->_left), node, len);
    else if(res > 0)
       return Insert(number, str, &((*node)->_right), node, len);
    else return false;
}
bool TAvlTree::Remove(char* str, TNode** node, size_t len)
{
    if((*node) == NULL) return false;
    int res = strncmp((*node)->_key, str,len + 1);
    if(res == 0) // we find suitable node
    {
        TNode* tmp = *node;
        TNode* parentOfNode = (*node)->_parent;

        if((*node)->_left == NULL && (*node)->_right == NULL)
        {
            bool src;
            if((*node)->_parent == NULL) src = false;
            else if((*node)->_parent->_left == (*node)) src = false;
            else src = true;

            *node = NULL;
            delete[] tmp->_key;
            tmp->_key = NULL;
            delete tmp;
            tmp = NULL;
            RecountBalanceDelete(parentOfNode, src);
            return true;
        }
        else if((*node)->_right != NULL && (*node)->_left == NULL)
        {
            bool src;
            if((*node)->_parent == NULL) src = false;
            else if((*node)->_parent->_left == (*node)) src = false;
            else src = true;

            (*node) = (*node)->_right;
            (*node)->_parent = tmp->_parent;
            delete[] tmp->_key;
            tmp->_key = NULL;
            delete tmp;
            tmp = NULL;
            RecountBalanceDelete(parentOfNode, src);
            return true;
        }
        else if((*node)->_left != NULL && (*node)->_right == NULL)
        {
            bool src;
            if((*node)->_parent == NULL) src = false;
            else if((*node)->_parent->_left == (*node)) src = false;
            else src = true;

            (*node) = (*node)->_left;
            (*node)->_parent = tmp->_parent;
            delete[] tmp->_key;
            tmp->_key = NULL;
            delete tmp;
            tmp = NULL;
            RecountBalanceDelete(parentOfNode, src);
            return true;
        }
        else
        {
            *node = (*node)->_right;
            TNode* tmp2 = *node;
            if((*node)->_left == NULL)
            {
                bool src;
                if(tmp->_left == (*node)) src = false;
                else src = true;

                (*node)->_parent = parentOfNode;
                (*node)->_balance = tmp->_balance;
                if(tmp->_left != NULL) tmp->_left->_parent = *node;
                (*node)->_left = tmp->_left;
                if(parentOfNode != NULL)
                {
                    if(parentOfNode->_left == *node) parentOfNode->_left = *node;
                    else parentOfNode->_right = *node;
                }
                delete[] tmp->_key;
                tmp->_key = NULL;
                delete tmp;
                tmp = NULL;
                RecountBalanceDelete(tmp2, src);
            }
            else //dive in _left branch untill NULL
            {
                while((*node)->_left != NULL)
                {
                    (*node) = (*node)->_left;
                }

                parentOfNode = (*node)->_parent;
                TNode* tmp2 = (*node)->_right;
                if(tmp2 != NULL)
                {
                    tmp2->_parent = parentOfNode;
                }
                parentOfNode->_left = tmp2;
                (*node)->_parent = tmp->_parent;
                (*node)->_right = tmp->_right;
                (*node)->_left = tmp->_left;
                (*node)->_balance = tmp->_balance;
                tmp->_left->_parent = (*node);
                tmp->_right->_parent = (*node);
                if(tmp->_parent != NULL)
                {
                    if(tmp->_parent->_left == tmp) tmp->_parent->_left = *node;
                    else if(tmp->_parent->_right == tmp) tmp->_parent->_right = *node;
                }
                delete[] tmp->_key;
                tmp->_key = NULL;
                delete tmp;
                tmp = NULL;
                RecountBalanceDelete(parentOfNode, false);
            }
            return true;
        }
    }
    else if(res < 0)
        return Remove(str, &(*node)->_left, len);
    else if(res > 0)
        return Remove(str, &(*node)->_right, len);
    else return false;
}
void TAvlTree::LkpSave(TNode* node, FILE* file)
{
    if(node == NULL) return;
    char buff[257];
    strcpy(buff, node->_key);
    fwrite(node, sizeof(TNode), 1, file);
    fwrite(buff, sizeof(buff), 1, file);
    LkpSave(node->_left, file);
    LkpSave(node->_right, file);
}
void TAvlTree::LkpLoad(TNode** node, TNode* _parent, FILE* file)
{
    TNode tmp;
    char tmpBuff[257];
    if(fread(&tmp, sizeof(TNode), 1,file) < 1) return;
    fread(tmpBuff, sizeof(tmpBuff), 1,file);
    *node = new TNode;
    **node = tmp;
    //if(*node == NULL) return;
    size_t size = strlen(tmpBuff);
    (*node)->_key = new char[size + 1];
    strncpy((*node)->_key, tmpBuff, size);
    (*node)->_key[size] = '\0';
    (*node)->_parent = _parent;
    if((*node)->_left != NULL) LkpLoad(&(*node)->_left,(*node), file);
    if((*node)->_right != NULL) LkpLoad(&(*node)->_right,(*node), file);
    else return;
}

