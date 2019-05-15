
#include "include/structs.h"
#include "include/memory.h"
#include "include/string.h"
#include "include/parsing.h"
#include "include/comands.h"

#define INT_TYPE 0
#define FLOAT_TYPE 1

int ExecuteComands(Parent *CmdList)
{
    Memory *memory = InitMemory();
    Operator *NeCmd = CmdList->next;
    while (NeCmd->next != NULL)
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
                printf("!!! Variable has not been defined previosly !!!\n");
            }
            printf("%s << ", NeCmd->Read->name);
            scanf("%f", &in->value);
        }
        else if (NeCmd->Write != NULL)
        {
            Variable *out = LookupVariable(memory, NeCmd->Write->name);
            if (out == NULL)
            {
                out = CreateNewVariable(memory, NeCmd->Write->name, (0.0F), FLOAT_TYPE);
                printf("!!! Variable has not been defined previosly !!!\n");
            }
            printf(">> %f - %s\n", out->value, out->name);
        }
        else if (NeCmd->Match != NULL)
        {
            Variable *Customer = LookupVariable(memory, NeCmd->Match->VarName);
            if (Customer == NULL)
            {
                Customer = CreateNewVariable(memory, NeCmd->Match->VarName, (0.0F), FLOAT_TYPE);
                printf("!!! Variable has not been defined previosly !!!\n");
            }
            switch (NeCmd->Match->Act)
            {
            case '+':;
                SumComand(Customer, memory, NeCmd);
                break;
            case '-':;
                DifComand(Customer, memory, NeCmd);
                break;
            case '*':;
                MultipComand(Customer, memory, NeCmd);
                break;
            case '/':;
                DivComand(Customer, memory, NeCmd);
                break;
            default:
                break;
            }
        }
        NeCmd = NeCmd->next;
    }
    return 0;
}
