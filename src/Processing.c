
#include "include/structs.h"
#include "include/memory.h"
#include "include/string.h"
#include "include/parsing.h"
#include "include/comands.h"
#include "include/Processing.h"

#define INT_TYPE 0
#define FLOAT_TYPE 1

int ExecuteComandsList(Memory *memory, Operator *NeCmd)
{
    while (NeCmd != NULL)
    {
        NeCmd = ExecuteComand(memory, NeCmd);
    }
    return 0;
}

Operator *ExecuteComand(Memory *memory, Operator *NeCmd)
{
    if (NeCmd->Var != NULL)
    {
        Variable *newvar = CreateNewVariable(memory, NeCmd->Var->name, NeCmd->Var->value, NeCmd->Var->type);
        printf("-------------\nInit new variable:\n");
        printf("Name: %s\n", newvar->name);
        printf("Type: %d\n", newvar->type);
        printf("Value: %f\n-------------\n", newvar->value);
    }
    else if (NeCmd->Read != NULL)
    {
        Variable *in = LookupVariable(memory, NeCmd->Read->name);
        if (in == NULL)
        {
            in = CreateNewVariable(memory, NeCmd->Read->name, (0.0F), FLOAT_TYPE);
            printf("!!! Variable <%s> has not been defined previosly !!!\n", NeCmd->Read->name);
        }
        printf("%s << ", NeCmd->Read->name);
        if (in->type == INT_TYPE)
        {
            scanf("%f", &in->value);
            in->value = (int)in->value;
        }
        else
        {
            scanf("%f", &in->value);
        }
    }
    else if (NeCmd->Write != NULL)
    {
        Variable *out = LookupVariable(memory, NeCmd->Write->name);
        if (out == NULL)
        {
            out = CreateNewVariable(memory, NeCmd->Write->name, (0.0F), FLOAT_TYPE);
            printf("!!! Variable <%s> has not been defined previosly !!!\n", NeCmd->Write->name);
        }
        if (out->type == INT_TYPE)
        {
            printf("%s >> %.0f\n", out->name, out->value);
        }
        else
        {
            printf("%s >> %f\n", out->name, out->value);
        }
    }
    else if (NeCmd->Match != NULL)
    {
        Variable *Customer = LookupVariable(memory, NeCmd->Match->VarName);
        if (Customer == NULL)
        {
            Customer = CreateNewVariable(memory, NeCmd->Match->VarName, (0.0F), FLOAT_TYPE);
            printf("!!! Variable <%s> has not been defined previosly !!!\n", NeCmd->Match->VarName);
        }
        MatchComand(Customer, memory, NeCmd, NeCmd->Match->Act);
    }
    else if (NeCmd->While != NULL)
    {
        int Result = 0;
        Result = ChekCondition(memory, NeCmd, NeCmd->While->Act);
        if (Result == 0)
        {
            return SkipCycle(NeCmd);
        }
    }
    else if (NeCmd->Done != NULL)
    {
        int Result = 0;
        Result = ChekCondition(memory, NeCmd->parent, NeCmd->parent->While->Act);
        if (Result == 1)
        {
            return NeCmd->parent;
        }
    }
    else if (NeCmd->If != NULL)
    {
        int Result = 0;
        Result = ChekIfCondition(memory, NeCmd, NeCmd->If->Act);
        if (Result == 0)
        {
            return GoToElseOrFi(NeCmd);
        }
    }
    else if (NeCmd->Else != NULL)
    {
        return SkipElse(NeCmd);
    }
    return NeCmd->next;
}
