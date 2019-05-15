#pragma once

typedef struct Variable
{
    char *name;
    int type;
    float value;
    struct Variable *next;
} Variable;

typedef struct
{
    int size;
    Variable *next;
} Memory;

typedef struct
{
    struct Operator *next;
} Parent;

//---------------

typedef struct
{
    char *name;
    int type;
    float value;
} FVar;

typedef struct
{
    char *name;
} FRead;

typedef struct
{
    char *name;
} FWrite;

typedef struct
{
    char *VarName;
    char Act;
    Variable *First;
    Variable *Second;
} Fmatch;

typedef struct Operator
{
    Parent *par;
    struct Operator *next;
    FVar *Var;
    FRead *Read;
    FWrite *Write;
    Fmatch *Match;
} Operator;