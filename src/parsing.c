#include <stdio.h>
#include <stdlib.h>

#include "include/string.h"
#include "include/structs.h"
#include "include/memory.h"
#include "include/parsing.h"

#define READ 1
#define WRITE 2
#define VAR 3
#define MATCH 4

#define INT_TYPE 0
#define FLOAT_TYPE 1

#define MAXVARNAME 15

FILE *OpenFile(char *name)
{
    FILE *script;
    script = fopen(name, "r");
    if (script == NULL)
    {
        printf("Could't open file!\n");
        return NULL;
    }
    return script;
}

Parent *ReadScript(char *name)
{
    Parent *begin = InitParent();
    FILE *script = OpenFile(name);
    Operator *op, *prevop;
    op = InterpLine(script, begin);
    if (op != NULL)
    {
        begin->next = op;
        prevop = op;
    }
    do
    {
        op = InterpLine(script, begin);
        if (op != NULL)
        {
            prevop->next = op;
            prevop = op;
        }
    } while (op != NULL);
    fclose(script);
    return begin;
}

Operator *InterpLine(FILE *script, Parent *begin)
{
    Operator *new = InitOperator(begin);
    char *str = malloc(126 * sizeof(char));
    if (fgets(str, 126, script) != NULL)
    {
        //check(str);
        StrToComand(str, new);
    }
    else
    {
        return NULL;
    }
    return new;
}

void StrToComand(char *str, Operator *newop)
{
    char *sc = str, *sc2 = str;
    int comid = 0;
    for (; *sc != '\n' && *sc != '\0'; sc++)
    {
        if (*sc == ' ')
        {
            *sc = '\0';
        }
    }
    *sc = '\0';
    comid = IdentOperator(sc2);
    for (; *sc2 != '\0'; sc2++)
    {
    }
    sc2++;
    sc = str;
    switch (comid)
    {
    case VAR:;
        FVar *newvar = malloc(sizeof(FVar));
        newop->Var = newvar;
        newvar->name = malloc(MAXVARNAME * sizeof(char));
        newvar->name = scpy(newvar->name, sc2);
        newvar->value = (0.0F);
        newvar->type = INT_TYPE;
        break;
    case WRITE:;
        FWrite *newwr = malloc(sizeof(newwr));
        newop->Write = newwr;
        newwr->name = malloc(MAXVARNAME * sizeof(char));
        newwr->name = scpy(newwr->name, sc2);
        break;
    case READ:;
        FRead *newread = malloc(sizeof(newread));
        newop->Read = newread;
        newread->name = malloc(MAXVARNAME * sizeof(char));
        newread->name = scpy(newread->name, sc2);
        break;
    case MATCH:;
        Fmatch *newmat = malloc(sizeof(Fmatch));
        newop->Match = newmat;
        Variable *fir = malloc(sizeof(Variable));
        Variable *sec = malloc(sizeof(Variable));
        newmat->VarName = malloc(MAXVARNAME * sizeof(char));
        newmat->VarName = scpy(newmat->VarName, sc);
        newmat->First = fir;
        newmat->Second = sec;
        for (; *sc != '='; sc++)
        {
        }
        sc = sc + 2;
        if (isdigi(*sc) == 0)
        {
            newmat->First->name = malloc(MAXVARNAME * sizeof(char));
            newmat->First->name = scpy(newmat->First->name, sc);
        }
        else
        {
            float buf;
            sscanf(sc, "%f", &buf);
            newmat->First->name = sc;
            newmat->First->value = buf;
            newmat->First->type = FLOAT_TYPE;
        }
        for (; *sc != '\0'; sc++)
        {
        }
        sc++;

        newmat->Act = *sc;

        for (; *sc != '\0'; sc++)
        {
        }
        sc++;
        if (isdigi(*sc) == 0)
        {
            newmat->Second->name = malloc(MAXVARNAME * sizeof(char));
            newmat->Second->name = scpy(newmat->Second->name, sc);
        }
        else
        {
            float buf;
            sscanf(sc, "%f", &buf);
            newmat->Second->name = sc;
            newmat->Second->value = buf;
            newmat->Second->type = FLOAT_TYPE;
        }
        break;

    default:
        break;
    }
}

int IdentOperator(char *word)
{
    if (scmp(word, "var") == 0)
    {
        return VAR;
    }
    if (scmp(word, "read") == 0)
    {
        return READ;
    }
    if (scmp(word, "write") == 0)
    {
        return WRITE;
    }
    return MATCH;
}

Parent *InitParent()
{
    Parent *begin = malloc(sizeof(begin));
    begin->next = NULL;
    return begin;
}

Operator *InitOperator(Parent *begin)
{
    Operator *newop = malloc(sizeof(Operator));
    newop->par = begin;
    newop->next = NULL;
    newop->Var = NULL;
    newop->Read = NULL;
    newop->Write = NULL;
    return newop;
}