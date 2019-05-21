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
#define WHILE 5
#define DONE 6
#define IF 7
#define FI 8
#define ELSE 9

#define INT_TYPE 0
#define FLOAT_TYPE 1

#define MAXVARNAME 15
#define MAXSTRLEN 126

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

Operator *ReadScript(char *name)
{
    Operator *begin = InitOperator(NULL);
    FILE *script = OpenFile(name);
    begin = EditComandList(begin, begin, script);
    fclose(script);
    return begin;
}

Operator *EditComandList(Operator *begin, Operator *parent, FILE *script)
{
    Operator *op, *prevop;
    prevop = begin;
    while (op != NULL)
    {
        op = InterpLine(script, parent);
        if (op != NULL)
        {

            if (op->While != NULL)
            {
                prevop->next = op;
                prevop = EditComandList(op, op, script);
                op = InterpLine(script, parent);
            }
            if (op->Done != NULL)
            {
                prevop->next = op;
                return op;
            }
            if (op->If != NULL)
            {
                prevop->next = op;
                prevop = EditComandList(op, op, script);
                op = InterpLine(script, parent);
            }
            if (op->Fi != NULL)
            {
                prevop->next = op;
                return op;
            }
            prevop->next = op;
            prevop = op;
        }
    }
    return begin;
}

Operator *InterpLine(FILE *script, Operator *parent)
{
    Operator *new = InitOperator(parent);
    char *str = malloc(MAXSTRLEN * sizeof(char));
    if (fgets(str, MAXSTRLEN, script) != NULL)
    {
        StrToComand(str, new);
    }
    else
    {
        free(new);
        return NULL;
    }
    free(str);
    return new;
}

void StrToComand(char *str, Operator *newop)
{
    char *sc2 = str;
    StrDelim(str);
    sc2 = MoveToNextDelim(sc2);
    int comid = IdentOperator(str);
    switch (comid)
    {
    case VAR:;
        AddVarComand(newop, sc2);
        break;
    case WRITE:;
        AddWriteComand(newop, sc2);
        break;
    case READ:;
        AddReadComand(newop, sc2);
        break;
    case MATCH:;
        AddMatchComand(newop, sc2, str);
        break;
    case WHILE:;
        AddWhileComand(newop, str);
        break;
    case DONE:;
        Fdone *newdone = malloc(sizeof(Fdone));
        newop->Done = newdone;
        break;
    case FI:;
        Ffi *newfi = malloc(sizeof(Ffi));
        newop->Fi = newfi;
        break;
    case ELSE:;
        Felse *newelse = malloc(sizeof(Felse));
        newop->Else = newelse;
        break;
    case IF:;
        AddIfComand(newop, str);
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
    if (scmp(word, "while") == 0)
    {
        return WHILE;
    }
    if (scmp(word, "done") == 0)
    {
        return DONE;
    }
    if (scmp(word, "if") == 0)
    {
        return IF;
    }
    if (scmp(word, "else") == 0)
    {
        return ELSE;
    }
    if (scmp(word, "fi") == 0)
    {
        return FI;
    }

    return MATCH;
}

Operator *InitOperator(Operator *parent)
{
    Operator *newop = malloc(sizeof(Operator));
    newop->parent = parent;
    newop->next = NULL;
    newop->Var = NULL;
    newop->Read = NULL;
    newop->Write = NULL;
    newop->Match = NULL;
    newop->Done = NULL;
    newop->While = NULL;
    newop->If = NULL;
    newop->Fi = NULL;
    newop->Else = NULL;
    return newop;
}

void AddVarComand(Operator *newop, char *str)
{
    FVar *newvar = malloc(sizeof(FVar));
    newop->Var = newvar;
    newvar->name = malloc(MAXVARNAME * sizeof(char));
    newvar->name = scpy(newvar->name, str);
    newvar->value = (0.0F);
    str = MoveToNextDelim(str);
    switch (*str)
    {
    case 'i':
        newvar->type = INT_TYPE;
        break;

    default:
        newvar->type = FLOAT_TYPE;
        break;
    }
}

void AddWriteComand(Operator *newop, char *str)
{
    FWrite *newwr = malloc(sizeof(newwr));
    newop->Write = newwr;
    newwr->name = malloc(MAXVARNAME * sizeof(char));
    newwr->name = scpy(newwr->name, str);
}

void AddReadComand(Operator *newop, char *str)
{
    FRead *newread = malloc(sizeof(newread));
    newop->Read = newread;
    newread->name = malloc(MAXVARNAME * sizeof(char));
    newread->name = scpy(newread->name, str);
}
void AddMatchComand(Operator *newop, char *sc2, char *sc)
{
    Fmatch *newmat = malloc(sizeof(Fmatch));
    newop->Match = newmat;
    newmat->VarName = malloc(MAXVARNAME * sizeof(char));
    newmat->VarName = scpy(newmat->VarName, sc);
    newmat->First = malloc(sizeof(Variable));
    newmat->Second = malloc(sizeof(Variable));
    sc = MoveToNextDelim(sc);
    sc = sc + 2;
    newmat->First->name = malloc(MAXVARNAME * sizeof(char));
    if (isdigi(*sc) == 0)
    {
        newmat->First->name = scpy(newmat->First->name, sc);
    }
    else
    {
        float buf;
        sscanf(sc, "%f", &buf);
        newmat->First->name = scpy(newmat->First->name, sc);
        newmat->First->value = buf;
        newmat->First->type = FLOAT_TYPE;
    }
    sc = MoveToNextDelim(sc);
    if (*sc != '-' && *sc != '+')
    {
        newmat->Act = '+';
        newmat->Second->name = "0";
        newmat->Second->value = 0;
        newmat->Second->type = FLOAT_TYPE;
    }
    else
    {
        newmat->Act = *sc;
        sc = MoveToNextDelim(sc);
        newmat->Second->name = malloc(MAXVARNAME * sizeof(char));
        if (isdigi(*sc) == 0)
        {
            newmat->Second->name = scpy(newmat->Second->name, sc);
        }
        else
        {
            float buf;
            sscanf(sc, "%f", &buf);
            newmat->Second->name = scpy(newmat->Second->name, sc);
            newmat->Second->value = buf;
            newmat->Second->type = FLOAT_TYPE;
        }
    }
}

void AddWhileComand(Operator *newop, char *sc)
{
    Fwhile *newwhile = malloc(sizeof(Fwhile));
    newop->While = newwhile;
    Variable *firs = malloc(sizeof(Variable));
    Variable *seco = malloc(sizeof(Variable));
    newwhile->First = firs;
    newwhile->Second = seco;
    sc = MoveToNextDelim(sc);
    if (isdigi(*sc) == 0)
    {
        newwhile->First->name = malloc(MAXVARNAME * sizeof(char));
        newwhile->First->name = scpy(newwhile->First->name, sc);
    }
    else
    {
        float buf;
        sscanf(sc, "%f", &buf);
        newwhile->First->name = malloc(MAXVARNAME * sizeof(char));
        newwhile->First->name = scpy(newwhile->First->name, sc);
        newwhile->First->value = buf;
        newwhile->First->type = FLOAT_TYPE;
    }
    sc = MoveToNextDelim(sc);
    newwhile->Act = *sc;
    if (newwhile->Act == '=')
    {
        sc = sc + 3;
    }
    else
    {
        sc = sc + 2;
    }
    if (isdigi(*sc) == 0)
    {
        newwhile->Second->name = malloc(MAXVARNAME * sizeof(char));
        newwhile->Second->name = scpy(newwhile->Second->name, sc);
    }
    else
    {
        float buf;
        sscanf(sc, "%f", &buf);
        newwhile->Second->name = malloc(MAXVARNAME * sizeof(char));
        newwhile->Second->name = scpy(newwhile->Second->name, sc);
        newwhile->Second->value = buf;
        newwhile->Second->type = FLOAT_TYPE;
    }
}

void AddIfComand(Operator *newop, char *str)
{
    Fif *newif = malloc(sizeof(Fif));
    newop->If = newif;
    Variable *firs = malloc(sizeof(Variable));
    Variable *seco = malloc(sizeof(Variable));
    newif->First = firs;
    newif->Second = seco;
    str = MoveToNextDelim(str);
    if (isdigi(*str) == 0)
    {
        newif->First->name = malloc(MAXVARNAME * sizeof(char));
        newif->First->name = scpy(newif->First->name, str);
    }
    else
    {
        float buf;
        sscanf(str, "%f", &buf);
        newif->First->name = malloc(MAXVARNAME * sizeof(char));
        newif->First->name = scpy(newif->First->name, str);
        newif->First->value = buf;
        newif->First->type = FLOAT_TYPE;
    }
    str = MoveToNextDelim(str);
    newif->Act = *str;
    if (newif->Act == '=')
    {
        str = str + 3;
    }
    else
    {
        str = str + 2;
    }
    if (isdigi(*str) == 0)
    {
        newif->Second->name = malloc(MAXVARNAME * sizeof(char));
        newif->Second->name = scpy(newif->Second->name, str);
    }
    else
    {
        float buf;
        sscanf(str, "%f", &buf);
        newif->Second->name = malloc(MAXVARNAME * sizeof(char));
        newif->Second->name = scpy(newif->Second->name, str);
        newif->Second->value = buf;
        newif->Second->type = FLOAT_TYPE;
    }
}