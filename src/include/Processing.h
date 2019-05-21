#pragma once

#include "structs.h"

int ExecuteComandsList(Memory *memory, Operator *CmdList);
Operator *ExecuteComand(Memory *memory, Operator *NeCmd);