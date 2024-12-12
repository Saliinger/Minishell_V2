*
#include "../../../include/safe_malloc.h"

void add_node_safe_malloc(t_safe_malloc *head, void *value)
{
    t_safe_malloc *block;

    block = (t_safe_malloc *)malloc(sizeof(t_safe_malloc));
    if (!block)
    {
        printerr("bash: xmalloc: cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    block->ptr = value;
    block->mark = false;
    block->next = NULL;
    if (!head)
        head = block;
    else
    {
        block->next = block;
        head = block;
    }
}

void *safe_destroy(t_safe_malloc *head)
{
    t_safe_malloc *next;

    while (head)
    {
        next = head->next;
        free(head->ptr);
        free(head);
        head = next;
    }
    return (NULL);
}

void    *safe_malloc(size_t size, enum e_action action)
{
    void            *ptr;
    static t_safe_malloc   *cmd;
    static t_safe_malloc   *minishell;

    ptr = malloc(size);
    if (!ptr)
    {
        printerr("bash: xmalloc: cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    if (action == ALLOC_COMMAND)
        add_node_safe_malloc(cmd, ptr);
    else if (action == ALLOC_MINISHELL)
        add_node_safe_malloc(minishell, ptr);
    else if (action == DESTROY_COMMAND)
        safe_destroy(cmd);
    else if (action == NUKE)
    {
        safe_destroy(cmd);
        safe_destroy(minishell);
        return (NULL);
    }
    return (ptr);
}

char *safe_strdup(char *s,  enum e_action action)
{
    char *dup = safe_malloc(ft_strlen(s) + 1, action);
    if (dup)
        ft_strcpy(dup, s);
    return (dup);
}