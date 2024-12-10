/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:19:26 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 23:19:47 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the middle of the list
t_export_list	*find_middle(t_export_list *head)
{
	t_export_list	*slow;
	t_export_list	*fast;

	slow = head;
	fast = head->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return (slow);
}

// Function to merge two sorted lists
t_export_list	*merge_sorted_lists(t_export_list *left, t_export_list *right)
{
	t_export_list	*result;

	if (!left)
		return (right);
	if (!right)
		return (left);
	result = NULL;
	if (strcmp(left->name, right->name) <= 0)
	{
		result = left;
		result->next = merge_sorted_lists(left->next, right);
	}
	else
	{
		result = right;
		result->next = merge_sorted_lists(left, right->next);
	}
	return (result);
}

void	merge_sort(t_export_list **head_ref)
{
	t_export_list	*head;
	t_export_list	*middle;
	t_export_list	*right_half;

	if (!head_ref || !*head_ref || !(*head_ref)->next)
		return ;
	head = *head_ref;
	middle = find_middle(head);
	right_half = middle->next;
	middle->next = NULL;
	merge_sort(&head);
	merge_sort(&right_half);
	*head_ref = merge_sorted_lists(head, right_half);
}
