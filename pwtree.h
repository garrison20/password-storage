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
int delete(PWTree_Ptr *, char *);
int read_data(PWTree_Ptr *);
int store_data(PWTree_Ptr *);
PWTree *find(PWTree *, char *);
int change_title(PWTree_Ptr *, char *, char *);
int change_username(PWTree_Ptr *, char *, char *);
int change_password(PWTree_Ptr *, char *, char *);
int show_username(PWTree_Ptr *, char *);
int show_password(PWTree_Ptr *, char *);

#endif