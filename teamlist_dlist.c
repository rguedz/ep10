#include "teamlist.h"
#include <stdlib.h>

struct node {
    Team *team;
    struct node *next;
    struct node *prev;
};

struct teamlist {
    struct node *first;
    struct node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL)
        return NULL;
    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL)
        return;

    n->team = t;
    n->next = NULL;
    n->prev = tl->last;

    if (tl->last == NULL)        
        tl->first = n;
    else                         
        tl->last->next = n;
    tl->last = n;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}


Team *tl_get(TeamList *tl, int i) {
    if (i < 0 || i >= tl->size)
        return NULL;

    struct node *n;
    if (i < tl->size / 2) {
        n = tl->first;
        for (int k = 0; k < i; k++)
            n = n->next;
    } else {
        n = tl->last;
        for (int k = tl->size - 1; k > i; k--)
            n = n->prev;
    }
    return n->team;
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;

    struct node *n = tl->first;
    while (n != NULL) {
        struct node *next = n->next;  
        team_free(n->team);            
        free(n);                     
        n = next;
    }
    free(tl);
}
