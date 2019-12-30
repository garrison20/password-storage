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

    read_data(pwtree);

    if (argc > 1) {
        if ((strcmp(argv[1], "-i") == 0) && (argc == 5)) {
            insert(pwtree, argv[2], argv[3], argv[4]);
        }
    }

    store_data(pwtree);

    return 0;
}