#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

FILE *OpenFile(char *name);
Operator *ReadScript(char *name);
Operator *EditComandList(Operator *begin, Operator *parent, FILE *script);
Operator *InterpLine(FILE *script, Operator *begin);
void StrToComand(char *str, Operator *newop);
int IdentOperator(char *word);
Operator *InitOperator(Operator *begin);

void AddVarComand(Operator *newop, char *str);
void AddWriteComand(Operator *newop, char *str);
void AddReadComand(Operator *newop, char *str);
void AddMatchComand(Operator *newop, char *sc2, char *sc);
void AddWhileComand(Operator *newop, char *sc);
void AddIfComand(Operator *newop, char *str);