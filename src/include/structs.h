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

typedef struct
{
    char Act;
    Variable *First;
    Variable *Second;
} Fwhile;

typedef struct
{
} Fdone;

typedef struct
{
    char Act;
    Variable *First;
    Variable *Second;
} Fif;

typedef struct
{
} Ffi;

typedef struct
{
} Felse;

typedef struct Operator
{
    struct Operator *parent;
    struct Operator *next;
    FVar *Var;
    FRead *Read;
    FWrite *Write;
    Fmatch *Match;
    Fdone *Done;
    Fwhile *While;
    Fif *If;
    Ffi *Fi;
    Felse *Else;
} Operator;