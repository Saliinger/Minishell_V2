/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:57:22 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/12 16:30:46 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/safe_malloc.h"

void *safe_destroy(t_safe_malloc **head_ref)
{
    t_safe_malloc *current_node;
    t_safe_malloc *next_node;

    current_node = *head_ref;
    while (current_node)
    {
        next_node = current_node->next;
        free(current_node->ptr);
        free(current_node);
        current_node = next_node;
    }
    *head_ref = NULL;
    return (NULL);
}

void add_node_safe_malloc(t_safe_malloc **head, void *value)
{
    t_safe_malloc *block;
    t_safe_malloc *temp;

    block = (t_safe_malloc *)malloc(sizeof(t_safe_malloc));
    if (!block)
    {
        printerr("bash: xmalloc: cannot allocate memory\n");
        safe_malloc(0, NUKE);
        exit(EXIT_FAILURE);
    }
    block->ptr = value;
    block->mark = false;
    block->next = NULL;
    if (!*head)
        *head = block;
    else
    {
        temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = block;
    }
}

void *safe_malloc(size_t size, enum e_action action)
{
    void *ptr;
    static t_safe_malloc *cmd = NULL;
    static t_safe_malloc *minishell = NULL;

    if (action == NUKE)
    {
        safe_destroy(&cmd);
        safe_destroy(&minishell);
        return (NULL);
    }
    else if (action == DESTROY_COMMAND)
    {
        safe_destroy(&cmd);
        return (NULL);
    }
    else
    {
        ptr = malloc(size);
        if (!ptr)
        {
            printerr("bash: xmalloc: cannot allocate memory\n");
            safe_destroy(&cmd);
            safe_destroy(&minishell);
            exit(EXIT_FAILURE);
        }
        if (action == ALLOC_COMMAND)
            add_node_safe_malloc(&cmd, ptr);
        else if (action == ALLOC_MINISHELL)
            add_node_safe_malloc(&minishell, ptr);
    }
    return (ptr);
}

char *safe_strdup(char *s, enum e_action action)
{
    char *dup = safe_malloc(ft_strlen(s) + 1, action);
    if (dup)
        ft_strcpy(dup, s);
    return (dup);
}
