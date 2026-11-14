#include "teamlist.h"
#include <stdlib.h>


#define TL_INITIAL_CAPACITY 4


struct teamlist {
    Team **data;
    int size;
    int capacity;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL)
        return NULL;

    tl->data = malloc(TL_INITIAL_CAPACITY * sizeof(Team *));
    if (tl->data == NULL) {
        free(tl);
        return NULL;
    }
    tl->size = 0;
    tl->capacity = TL_INITIAL_CAPACITY;
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl->size == tl->capacity) {
        int new_capacity = tl->capacity * 2;
        Team **new_data = realloc(tl->data, new_capacity * sizeof(Team *));
        if (new_data == NULL)
            return;
        tl->data = new_data;
        tl->capacity = new_capacity;
    }
    tl->data[tl->size] = t;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (i < 0 || i >= tl->size)
        return NULL;
    return tl->data[i];
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;
    for (int i = 0; i < tl->size; i++)
        team_free(tl->data[i]);  
    free(tl->data);              
    free(tl);                    
}
