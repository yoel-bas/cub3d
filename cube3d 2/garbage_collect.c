/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:16:12 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/13 22:33:46 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_gc	*new_garbage(void *value)
{
	t_gc	*garbage;
	garbage = malloc(sizeof(t_gc));
	if (garbage != NULL)
	{
		garbage->data = value;
		garbage->next = NULL;
	}
	return (garbage);
}

void	add_garbage(t_gc **garbage, t_gc *new)
{
	t_gc	*last;

	if (!new)
		return;
	if (!*garbage)
	{
		*garbage = new;
		return ;
	}
	last = *garbage;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}
