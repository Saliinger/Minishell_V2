*
#include "../../../include/safe_malloc.h"

void    *safe_malloc(size_t size, t_safe_malloc *head)
{
    void            *ptr;
    t_safe_malloc   *block;

    ptr = malloc(size);
    if (!ptr)
    {
        printerr("bash: xmalloc: cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    block = (t_safe_malloc *)malloc(sizeof(t_safe_malloc));
    if (!block)
    {
        printerr("bash: xmalloc: cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    block->ptr = ptr;
    block->mark = false;
    block->next = NULL;
    if (!head)
        head = block;
    else
    {
        block->next = head;
        head = block;
    }
    return (ptr);
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

char *safe_strdup(char *s,  t_safe_malloc *head)
{
    char *dup = safe_malloc(ft_strlen(s) + 1, head);
    if (dup)
        ft_strcpy(dup, s);
    return (dup);
}