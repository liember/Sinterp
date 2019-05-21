#include <stdio.h>
#include <stdlib.h>

#include "include/structs.h"
#include "include/string.h"

#define MAXVARNAME 15

Memory *InitMemory()
{
    Memory *p;
    p = malloc(sizeof(*p));
    if (p != NULL)
    {
        p->next = NULL;
        p->size = 0;
    }
    return p;
}

Variable *LookupVariable(Memory *mem, char *name)
{
    if (mem != NULL)
    {
        Variable *list = mem->next;
        for (; list != NULL; list = list->next)
        {
            if (scmp(list->name, name) == 0)
            {
                return list;
            }
        }
    }

    return NULL;
}

Variable *CreateNewVariable(Memory *mem, char *name, float value, int type)
{
    Variable *p = malloc(sizeof(*p));
    if (p != NULL)
    {
        p->name = name;
        p->value = value;
        p->type = type;
        p->next = mem->next;
        mem->next = p;
        mem->size++;
    }
    return p;
}

Variable *DeleteVariable(Memory *mem, char *name)
{
    if (mem != NULL)
    {
        Variable *list = mem->next;
        Variable *p, *prev = NULL;
        for (p = list; p != NULL; p = p->next)
        {
            if (scmp(p->name, name) == 0)
            {
                if (prev == NULL)
                {
                    mem->next = p->next;
                }
                else
                    prev->next = p->next; /* Есть элемент слева */
                free(p);                  /* Освобождаем память */
                return list;              /* Указатель на новую голову */
            }
            prev = p; /* Запоминаем предыдущий элемент */
        }
    }
    return NULL; /* Не нашли */
}