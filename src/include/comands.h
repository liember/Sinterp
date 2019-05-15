#pragma once

#include "structs.h"
#include "memory.h"
#include "string.h"
#include "parsing.h"

void SumComand(Variable *Customer, Memory *memory, Operator *NeCmd);
void DifComand(Variable *Customer, Memory *memory, Operator *NeCmd);
void MultipComand(Variable *Customer, Memory *memory, Operator *NeCmd);
void DivComand(Variable *Customer, Memory *memory, Operator *NeCmd);
