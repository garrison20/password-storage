#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwtree.h"

PWTree *create_node(char *, char *, char *);
PWTree *create_empty_node();
void free_node(PWTree *);


/* Initializes an empty tree pointer to point to a single node
with an "empty" status. This means all string values of the node
are equal to NULL and the "empty" status is equal to true (1). */
PWTree_Ptr *initialize() {
    int output = 0;
    PWTree *node = NULL;
    PWTree_Ptr *pwtree = malloc(sizeof(*pwtree)); 
    if (pwtree != NULL) {
        node = create_empty_node();
        if (node != NULL) {
            pwtree->empty = 1;
            pwtree->head = node;
            pwtree->tail = pwtree->head;
        } else {
            /* Delete whole tree since first empty node can't be made */
            free(pwtree);
            pwtree = NULL;
        }
    }

    return pwtree;
}

/* This function inserts a new node into the linked list used for storing
all entries in the log. There are two possibilities for insertion: inserting
a node in an empty list, which involves changing the contents of the empty node,
or inserting an entirely new node. Any successful insertion changes the "empty"
status to false (0). */
int insert(PWTree_Ptr *pwtree, char *title, char *username, char *password) {
    PWTree *node = NULL;
    PWTree *temp = NULL;

    if (pwtree != NULL) {
        /* If tree is empty, insert first node. Change all the null values
        to dynamically allocated string containers and copy in the new 
        string values. */
        if (pwtree->empty) {
            node = pwtree->head;

            node->title = malloc((int) strlen(title) + 1);
            if (node->title != NULL)
                strcpy(node->title, title);
            else 
                return 0;

            node->username = malloc((int) strlen(username) + 1);
            if (node->username != NULL)
                strcpy(node->username, username);
            else 
                return 0;

            node->password = malloc((int) strlen(password) + 1);
            if (node->password != NULL)
                strcpy(node->password, password);
            else 
                return 0;

            pwtree->empty = 0;
            pwtree->tail = pwtree->head;
        /* If the tree is not empty, then insert a new node and adjust the tail. */
        } else {
            node = create_node(title, username, password);
            pwtree->tail->next = node;
            pwtree->tail = pwtree->tail->next;
        }
    }

    return 1;
}

/* This function deletes a node with the same title as the one passed in.
All types of checks for the head node, middle nodes, and tail node are 
specified below. */
int delete(PWTree_Ptr *pwtree, char *title) {
    PWTree *curr = NULL, *prev = NULL;

    if (pwtree!= NULL) {
        if (pwtree->empty)
            return 1;

        curr = pwtree->head;

        printf("%s\n", curr->title);


        while ((curr != NULL) && (strcmp(curr->title, title) != 0)) {
            prev = curr;
            curr = curr->next;
        }

        if (prev == NULL) {
            /* Head node */
            if (curr != NULL) {
                /* Only one node */
                if (curr->next == NULL) {
                    /* Delete head node and reset tree to empty status */
                    free_node(curr);
                    pwtree->head = create_empty_node();
                    pwtree->tail = pwtree->head;
                /* More than one node */
                } else {
                    free_node(curr);
                    pwtree->head = pwtree->head->next;
                }
            }
        /* Not at head node */
        } else {
            /* Match found somewhere after head node */
            if (curr != NULL) {
                /* Delete tail node */
                if (curr->next == NULL) {
                    free(curr);
                    prev->next = NULL;
                    pwtree->tail = prev;
                /* Delete node somewhere in the middle */
                } else {
                    printf("%s\n", curr->next->title);
                    prev->next = curr->next;
                    free(curr);
                }
            } else 
                return 0;
        } 
    } else 
        return 0;

    return 1;
}

/* All strings are give a max length of 50 characters. A file pointer is opened
and the contents of the file are parsed three strings at a time, storing each string
in a new node's title, username, and password strings. */
int read_data(PWTree_Ptr *pwtree) {
    FILE *pwfile;
    char title[50], username[50], password[50];

    if (pwtree != NULL) {
        pwfile = fopen("pstorage.txt", "r");
        if (pwfile != NULL) {
            while (fscanf(pwfile, " %s %s %s", title, username, password) != EOF) {
                /* This check is used to prevent an empty file from storing 
                gargabe data. */
                if (title == NULL || username == NULL || password == NULL)
                    break;
                insert(pwtree, title, username, password);
            }

            fclose(pwfile);
        }
    } else 
        return 0;

    return 1;
}

int store_data(PWTree_Ptr *pwtree) {
    FILE *pwfile;
    PWTree *node;

    if (pwtree != NULL) {
        node = pwtree->head;

        pwfile = fopen("pstorage.txt", "w");

        while (node != NULL) {
            if (node->title == NULL || node->username == NULL || node->password == NULL)
                break;
                
            fprintf(pwfile, "%s\n%s\n%s\n\n", node->title, node->username, node->password);
            node = node->next;
        }

        fclose(pwfile);
    } else
        return 0;
    
    return 1;
}

/*******************************************************************/

/* All "change" functions follow the same patter for changing one of 
the strings tied to a node. The node is found with the find function,
then the respective string is changed by freeing it and then allocting
memory for a new string to be copied in. */

int change_title(PWTree_Ptr *pwtree, char *title, char *new_title) {
    PWTree *temp = NULL;

    if (pwtree != NULL) {
        temp = find(pwtree->head, title);
        if (temp != NULL) {
            free(temp->title);
            temp->title = NULL;
            temp->title = malloc((int) strlen(new_title) + 1);
            if (temp != NULL) {
                strcpy(temp->title, new_title);
            } else 
                return 0;
        } else 
            return 0;
    } else 
        return 0;
    
    return 1;
}

int change_username(PWTree_Ptr *pwtree, char *title, char *new_username) {
    PWTree *temp = NULL;

    if (pwtree != NULL) {
        temp = find(pwtree->head, title);
        if (temp != NULL) {
            free(temp->username);
            temp->username = NULL;
            temp->username = malloc((int) strlen(new_username) + 1);
            if (temp != NULL) {
                strcpy(temp->username, new_username);
            } else 
                return 0;
        } else 
            return 0;
    } else 
        return 0;
    
    return 1;
}

int change_password(PWTree_Ptr *pwtree, char *title, char *new_password) {
    PWTree *temp = NULL;

    if (pwtree != NULL) {
        temp = find(pwtree->head, title);
        if (temp != NULL) {
            free(temp->password);
            temp->password = NULL;
            temp->password = malloc((int) strlen(new_password) + 1);
            if (temp != NULL) {
                strcpy(temp->password, new_password);
            } else 
                return 0;
        } else 
            return 0;
    } else 
        return 0;
    
    return 1;
}

/*******************************************************************/

/* Parses through a list and returns the node if it's title matches the
one given. */
PWTree *find(PWTree *curr, char *title) {
    while ((curr != NULL) && (strcmp(curr->title, title) != 0)) {
        curr = curr->next;
    }

    return curr;
}

PWTree *create_node(char *title, char *username, char *password) {
    PWTree *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->title = malloc((int) strlen(title) + 1);
        if (node->title != NULL)
            strcpy(node->title, title);

        node->username = malloc((int) strlen(username) + 1);
        if (node->username != NULL)
            strcpy(node->username, username);

        node->password = malloc((int) strlen(password) + 1);
        if (node->password != NULL)
            strcpy(node->password, password);

        node->next= NULL;

        /* If any string in the node failed to be created, then
        free all aspects of the node and set it to NULL. */
        if ((node->title == NULL)
            || (node->username == NULL)
            || (node->password == NULL)) {
                free(node->title);
                free(node->username);
                free(node->password);
                node->title = NULL;
                node->username = NULL;
                node->password = NULL;
                node = NULL;
            }
    }

    return node;
}

/* Create a node with all values set to NULL. 
Used for creating an empty list. */
PWTree *create_empty_node() {
    PWTree *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->title = NULL;
        node->username = NULL;
        node->password = NULL;
        node->next = NULL;
    }

    return node;
}

/* Free all strings in the given struct and then free the struct. */
void free_node(PWTree *node) {
    free(node->title);
    free(node->username);
    free(node->password);
    free(node);
}