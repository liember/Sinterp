#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

Variable *DeleteVariable(Memory *mem, char *name);
Variable *LookupVariable(Memory *mem, char *name);
Variable *CreateNewVariable(Memory *mem, char *name, float value, int type);
Memory *InitMemory();