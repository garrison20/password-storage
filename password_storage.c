#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwtree.h"

/* Three options: */
/*  1. add username, password, and site name
    2. change password
    3. change username
    4. delete group or any specific line
*/

int main(int argc, char *argv[]) {
    PWTree_Ptr *pwtree = initialize();

    insert(pwtree, "Test", "robbyd", "12345");
    insert(pwtree, "Test2", "rgd", "678910");
    insert(pwtree, "Test3", "rgdddd", "67891dddd0");

    printf("%s\n", pwtree->tree->next->next->title);

    return 0;
}