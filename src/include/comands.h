#pragma once

#include "structs.h"
#include "memory.h"
#include "string.h"
#include "parsing.h"

void MatchComand(Variable *Customer, Memory *memory, Operator *NeCmd, char Act);

int ChekCondition(Memory *memory, Operator *NeCmd, char Act);

Operator *SkipCycle(Operator *NeCmd);

Operator *GoToElseOrFi(Operator *NeCmd);
Operator *SkipElse(Operator *NeCmd);

int ChekIfCondition(Memory *memory, Operator *NeCmd, char Act);
