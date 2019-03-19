#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include "TAvlTree.h"
#include "node.h"
using namespace std;
void ToLowerCase(char* Buffer)
{
    for(int i = 0; i < 256; ++i)
    {
        if(Buffer[i] == '\0' || Buffer[i] == '\n') break;
        if(Buffer[i] >= 'A' && Buffer[i] <= 'Z')
        {
            Buffer[i] += 32;
        }
    }
}
int main(int argc, char* argv[])
{
    TAvlTree* tree = new TAvlTree();
    unsigned long long int tmpVal;
    int command = getchar();
    char tmpStr[256];
    while(command != EOF)
    {
        if(command == '+') // add
        {
            scanf("%s", tmpStr);
            ToLowerCase(tmpStr);
            size_t len = strlen(tmpStr);
            scanf("%llu", &tmpVal);
            getchar();
            tree->Insert(tmpVal, tmpStr, &(tree->Root), NULL, len);
        }
        else if(command == '-') // delete
        {

            scanf("%s", tmpStr);
            ToLowerCase(tmpStr);
            size_t len = strlen(tmpStr);
            getchar();
            if(tree->Remove(tmpStr, &(tree->Root), len)) printf("OK\n");
            else printf("NoSuchWord\n");
        }
        else if(command == '!')
        {
            getchar();// skip space
            command = getchar();

            if(command == 'L') // Load
            {
                while(command != ' ') command = getchar();
                scanf("%s", tmpStr); // path/to/file
                getchar();
                FILE* fPtr = fopen(tmpStr, "r");
                if(fPtr == NULL)
                {
                    perror("ERROR: can't open file");
                    while(command != '\n') command = getchar();
                    continue;
                }
                tree->SimpleDelete(tree->Root);// we will delete all nodes!
                tree->Root = NULL;
                tree->LkpLoad(&(tree->Root), NULL, fPtr); // load new tree
                fclose(fPtr);
                printf("OK\n");
            }
            else // Save
            {
                while(command != ' ') command = getchar();
                scanf("%s", tmpStr); // path/to/file
                getchar();
                FILE* fPtr = fopen(tmpStr, "w");
                if(fPtr == NULL)
                {
                    perror("ERROR: can't open file");
                    while(command != '\n') command = getchar();
                    continue;
                }
                tree->LkpSave(tree->Root, fPtr);
                fclose(fPtr);
                printf("OK\n");
            }
        }
        else // search
        {
            ungetc(command, stdin);
            scanf("%s", tmpStr);
            ToLowerCase(tmpStr);
            size_t len = strlen(tmpStr);
            getchar();
            tree->Search(tmpStr, &(tree->Root), len);
        }
        command = getchar();
    }
    delete tree;
    return 0;
}

