//
// Created by Alexis Noukan on 12/12/2024.
//

#ifndef MINISHELL_V2_SAFE_MALLOC_H
#define MINISHELL_V2_SAFE_MALLOC_H

#include "imports.h"

typedef struct s_safe_malloc
{
    void                    *ptr;
    bool                    mark;
    struct s_safe_malloc    *next;
}                           t_safe_malloc;

// sert a creer des mallocs dans une liste chaine
void    *safe_malloc(size_t size, t_safe_malloc *head);

// sert a free le garbage collector
void *safe_destroy(t_safe_malloc *head);

// strdup but safe
char *safe_strdup(char *s, t_safe_malloc *head);

#endif //MINISHELL_V2_SAFE_MALLOC_H
