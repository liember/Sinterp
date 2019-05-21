

#include "include/structs.h"
#include "include/memory.h"
#include "include/string.h"
#include "include/parsing.h"

#define INT_TYPE 0
#define FLOAT_TYPE 1

//mathch

void MatchComand(Variable *Customer, Memory *memory, Operator *NeCmd, char Act)
{
    float fbuf = (0.0F), secbuf = (0.0F);
    Variable *fvar = LookupVariable(memory, NeCmd->Match->First->name);
    if (fvar == NULL)
    {
        fvar = CreateNewVariable(memory, NeCmd->Match->First->name, NeCmd->Match->First->value, FLOAT_TYPE);
        if (isdigi(*NeCmd->Match->First->name) != 1)
        {
            printf("!!! Variable has not been defined previosly !!!\n");
        }
    }
    Variable *svar = LookupVariable(memory, NeCmd->Match->Second->name);
    if (svar == NULL)
    {
        svar = CreateNewVariable(memory, NeCmd->Match->Second->name, NeCmd->Match->Second->value, FLOAT_TYPE);
        if (isdigi(*NeCmd->Match->Second->name) != 1)
        {
            printf("!!! Variable has not been defined previosly !!!\n");
        }
    }

    if (fvar->type == INT_TYPE && svar->type == INT_TYPE)
    {
    }
    else if (fvar->type == FLOAT_TYPE && svar->type == FLOAT_TYPE)
    {
    }
    else
    {
        printf("!!! Warning <%s> <%s> has different types !!!\n", fvar->name, svar->name);
    }

    fbuf = fvar->value;
    secbuf = svar->value;
    switch (Act)
    {
    case '+':
        if (Customer->type == INT_TYPE)
        {
            Customer->value = (int)fbuf + (int)secbuf;
        }
        else
        {
            Customer->value = fbuf + secbuf;
        }
        break;
    case '-':
        if (Customer->type == INT_TYPE)
        {
            Customer->value = (int)fbuf - (int)secbuf;
        }
        else
        {
            Customer->value = fbuf - secbuf;
        }
        break;

    default:
        printf("undifined act\n");
        break;
    }
}

//logic
int ChekCondition(Memory *memory, Operator *NeCmd, char Act)
{
    float fbuf = (0.0F), secbuf = (0.0F);
    Variable *fvar = LookupVariable(memory, NeCmd->While->First->name);
    if (fvar == NULL)
    {
        fvar = CreateNewVariable(memory, NeCmd->While->First->name, NeCmd->While->First->value, FLOAT_TYPE);
        if (isdigi(*NeCmd->While->First->name) != 1)
        {
            printf("!!! Variable has not been defined previosly !!!\n");
        }
    }
    Variable *svar = LookupVariable(memory, NeCmd->While->Second->name);
    if (svar == NULL)
    {
        svar = CreateNewVariable(memory, NeCmd->While->Second->name, NeCmd->While->Second->value, FLOAT_TYPE);
        if (isdigi(*NeCmd->While->Second->name) != 1)
        {
            printf("!!! Variable has not been defined previosly !!!\n");
        }
    }

    if (fvar->type == INT_TYPE && svar->type == INT_TYPE)
    {
    }
    else if (fvar->type == FLOAT_TYPE && svar->type == FLOAT_TYPE)
    {
    }
    else
    {
        printf("!!! Warning <%s> <%s> has different types !!!\n", fvar->name, svar->name);
    }

    fbuf = fvar->value;
    secbuf = svar->value;
    switch (Act)
    {
    case '<':
        if (fbuf < secbuf)
        {
            return 1;
        }
        break;
    case '>':
        if (fbuf > secbuf)
        {
            return 1;
        }
        break;
    case '=':
        if (fbuf == secbuf)
        {
            return 1;
        }
        break;
    default:
        break;
    }

    return 0;
}
int ChekIfCondition(Memory *memory, Operator *NeCmd, char Act)
{
    float fbuf = (0.0F), secbuf = (0.0F);
    Variable *fvar = LookupVariable(memory, NeCmd->If->First->name);
    if (fvar == NULL)
    {
        fvar = CreateNewVariable(memory, NeCmd->If->First->name, NeCmd->If->First->value, FLOAT_TYPE);
        if (isdigi(*NeCmd->If->First->name) != 1)
        {
            printf("!!! Variable <%s> has not been defined previosly !!!\n", NeCmd->If->First->name);
        }
    }
    Variable *svar = LookupVariable(memory, NeCmd->If->Second->name);
    if (svar == NULL)
    {
        svar = CreateNewVariable(memory, NeCmd->If->Second->name, NeCmd->If->Second->value, FLOAT_TYPE);
        if (isdigi(*NeCmd->If->Second->name) != 1)
        {
            printf("!!! Variable <%s> has not been defined previosly !!!\n", NeCmd->If->Second->name);
        }
    }

    if (fvar->type == INT_TYPE && svar->type == INT_TYPE)
    {
    }
    else if (fvar->type == FLOAT_TYPE && svar->type == FLOAT_TYPE)
    {
    }
    else
    {
        printf("!!! Warning <%s> <%s> has different types !!!\n", fvar->name, svar->name);
    }
    fbuf = fvar->value;
    secbuf = svar->value;
    switch (Act)
    {
    case '<':
        if (fbuf < secbuf)
        {
            return 1;
        }
        break;
    case '>':
        if (fbuf > secbuf)
        {
            return 1;
        }
        break;
    case '=':
        if (fbuf == secbuf)
        {
            return 1;
        }
        break;
    default:
        break;
    }

    return 0;
}

//operators
Operator *SkipCycle(Operator *NeCmd)
{
    Operator *sciping = NeCmd;
    for (int stoper = 0; NeCmd->next != NULL && stoper != 1; NeCmd = NeCmd->next)
    {
        if (NeCmd->Done != NULL)
        {
            if (NeCmd->parent == sciping)
            {
                stoper = 1;
            }
        }
    }
    return NeCmd;
}

Operator *GoToElseOrFi(Operator *NeCmd)
{
    Operator *sciping = NeCmd;
    for (int stoper = 0; NeCmd->next != NULL && stoper != 1; NeCmd = NeCmd->next)
    {
        if (NeCmd->Else != NULL || NeCmd->Fi != NULL)
        {
            if (NeCmd->parent == sciping)
            {
                stoper = 1;
            }
        }
    }
    return NeCmd;
}

Operator *SkipElse(Operator *NeCmd)
{
    Operator *sciping = NeCmd->parent;
    for (int stoper = 0; NeCmd->next != NULL && stoper != 1; NeCmd = NeCmd->next)
    {
        if (NeCmd->Fi != NULL)
        {
            if (NeCmd->parent == sciping)
            {
                stoper = 1;
            }
        }
    }
    return NeCmd;
}
