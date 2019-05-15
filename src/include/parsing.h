#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

FILE *OpenFile(char *name);
Parent *ReadScript(char *name);
Operator *InterpLine(FILE *script, Parent *begin);
void StrToComand(char *str, Operator *newop);
int IdentOperator(char *word);
Parent *InitParent();
Operator *InitOperator(Parent *begin);