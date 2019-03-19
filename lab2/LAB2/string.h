#ifndef STRING
#define STRING
#include <cstdio>
class TString
{
public:
    TString(const char* str);
    TString();
    ~TString();
    void Print();
    char* GetStr();
private:
    size_t Size;
    size_t Capacity;
    char* Buffer;
};

#endif // STRING

