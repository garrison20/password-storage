#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwtree.h"

PWTree *create_node(char *, char *, char *);

PWTree_Ptr *initialize() {
    int output = 0;
    PWTree *node = NULL;
    PWTree_Ptr *pwtree = malloc(sizeof(*pwtree)); 
    if (pwtree != NULL) {
        node = malloc(sizeof(*node));
        if (node != NULL) {
            pwtree->empty = 1;
            node->title = NULL;
            node->username = NULL;
            node->password = NULL;
            node->next = NULL;
            pwtree->head = node;
            pwtree->tail = pwtree->head;
        } else {
            /* Delete whole tree since first empty node can't be made */
            free(node);
            pwtree = NULL;
        }
    }

    return pwtree;
}

int insert(PWTree_Ptr *pwtree, char *title, char *username, char *password) {
    PWTree *node = NULL;
    PWTree *temp = NULL;

    if (pwtree != NULL) {
        /* If tree is empty, insert first node */
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
        } else {
            node = create_node(title, username, password);
            pwtree->tail->next = node;
            pwtree->tail = pwtree->tail->next;
        }
    }

    return 1;
}

int read_data(PWTree_Ptr *pwtree) {
    FILE *pwfile;
    char title[50], username[50], password[50];

    if (pwtree != NULL) {
        pwfile = fopen("pstorage.txt", "r");
        if (pwfile != NULL) {
            while (fscanf(pwfile, " %s %s %s", title, username, password) != EOF) {
                if (title == NULL || username == NULL || password == NULL)
                    break;
                insert(pwtree, title, username, password);
            }

            fclose(pwfile);
        }

        printf("%d\n", pwtree->empty);
        
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