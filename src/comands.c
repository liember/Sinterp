

#include "include/structs.h"
#include "include/memory.h"
#include "include/string.h"
#include "include/parsing.h"

#define INT_TYPE 0
#define FLOAT_TYPE 1

void SumComand(Variable *Customer, Memory *memory, Operator *NeCmd)
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
    fbuf = fvar->value;
    secbuf = svar->value;
    Customer->value = fbuf + secbuf;
}

void DifComand(Variable *Customer, Memory *memory, Operator *NeCmd)
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
    fbuf = fvar->value;
    secbuf = svar->value;
    Customer->value = fbuf - secbuf;
}

void MultipComand(Variable *Customer, Memory *memory, Operator *NeCmd)
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
    fbuf = fvar->value;
    secbuf = svar->value;
    Customer->value = fbuf * secbuf;
}

void DivComand(Variable *Customer, Memory *memory, Operator *NeCmd)
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
    fbuf = fvar->value;
    secbuf = svar->value;
    Customer->value = fbuf / secbuf;
}
