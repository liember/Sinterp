#include <stdio.h>
#include <stdlib.h>

#include "include/structs.h"
#include "include/memory.h"
#include "include/string.h"
#include "include/parsing.h"
#include "include/Processing.h"

int main(void)
{
    //CheckSyntax(ComandsList);
    Parent *ComandsList = ReadScript("input.txt");
    //CheckLogic(ComandsList);
    ExecuteComands(ComandsList);
    return 0;
}
