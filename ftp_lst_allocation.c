/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_lst_allocation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:50:03 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/06 20:42:30 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_lst_clear(t_lst **lst, va_list *va)
{
	t_lst	*link;

	while (*lst)
	{
		link = *lst;
		*lst = (*lst)->next;
		free(link->ptr);
		free(link);
	}
	va_end(*va);
	return (-1);
}

int	ftp_lst_malloc(t_lst **lst, char **ptr, size_t size)
{
	t_lst	*link;

	*ptr = malloc(size);
	if (!*ptr)
		return (-1);
	link = malloc(sizeof(*link));
	if (!link)
	{
		free(*ptr);
		*ptr = NULL;
		return (-1);
	}
	link->ptr = *ptr;
	link->next = *lst;
	*lst = link;
	return (0);
}

void	ftp_lst_free(t_lst **lst, void *ptr)
{
	t_lst	**l_ptr;
	t_lst	*next;

	if (!ptr)
		return ;
	l_ptr = lst;
	while ((*l_ptr)->ptr != ptr)
		l_ptr = &((*l_ptr)->next);
	next = (*l_ptr)->next;
	free((*l_ptr)->ptr);
	free(*l_ptr);
	*l_ptr = next;
}
