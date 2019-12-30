#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwtree.h"

/* This program allows the user to create a log for storing the company
name their username and password are for and the respective username and 
password. Entries, meaning the given company title and its respective 
username and password, can be deleted, new ones can be inserted, and 
current ones can have any of the three data entries modified. All data
exists in a file titled "pstorage.txt", which is handled in the other 
file titled "pwtree.c". */
int main(int argc, char *argv[]) {
    PWTree_Ptr *pwtree = initialize();

    read_data(pwtree);

    if (argc > 1) {
        if (argc == 3) {
            /* Delete entry */
            if (strcmp(argv[1], "-d") == 0) {
                /* delete a node with the same title as the one given */
                delete(pwtree, argv[2]);
            }
        } else if (argc == 4) {
            /* Change title */
            if (strcmp(argv[1], "-ct") == 0) 
                change_title(pwtree, argv[2], argv[3]);
            /* Change username */
            else if (strcmp(argv[1], "-cu") == 0) 
                change_username(pwtree, argv[2], argv[3]);
            /* Change password */
            else if (strcmp(argv[1], "-cp") == 0) 
                change_password(pwtree, argv[2], argv[3]);
        } else if (argc == 5) {
            /* Insert new entry */
            if (strcmp(argv[1], "-i") == 0) 
                insert(pwtree, argv[2], argv[3], argv[4]);
        }
    }

    store_data(pwtree);

    return 0;
}