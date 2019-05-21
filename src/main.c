#include <stdio.h>
#include <stdlib.h>

#include "include/structs.h"
#include "include/memory.h"
#include "include/string.h"
#include "include/parsing.h"
#include "include/Processing.h"

int main(int argc, const char *argv[])
{
    char script[100];
    if (argc != 2)
    {
        printf("Wrong number of arguments\n");
        return 1;
    }
    scpy(script, argv[1]);
    Operator *ComandsList = ReadScript(script);
    for (Operator *lol = ComandsList; lol != NULL; lol = lol->next)
    {
        printf("%p ne %p par %p\n", lol, lol->next, lol->parent);
    }
    Memory *memory = InitMemory();
    ExecuteComandsList(memory, ComandsList);
    return 0;
}
