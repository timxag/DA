#ifndef TNUMVEC_H_
#define TNUMVEC_H_

#include "TStruct.h"
#include <stdlib.h>

void InitTNumVec(TNumVec * vec);
void AddItem(TNumVec * vec, unsigned int number, char * string);
TItem GetItem(TNumVec * vec, const int i);
void DeleteTNumVec(TNumVec * vec);

#endif // TNUMVEC_H_