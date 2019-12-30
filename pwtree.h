#ifndef PWTREE
#define PWTREE

typedef struct pwtree {
    char *title;
    char *username;
    char *password;
    struct pwtree *next;
} PWTree;

typedef struct {
    PWTree *head;
    PWTree *tail;
    int empty;
} PWTree_Ptr;

PWTree_Ptr *initialize();
int insert(PWTree_Ptr *, char *, char *, char *);
int read_data(PWTree_Ptr *);
int store_data(PWTree_Ptr *);


int find(PWTree *, char *);
int delete_entry(PWTree *, char *);
int change_username(PWTree *, char *);
int change_password(PWTree *, char *);
#endif