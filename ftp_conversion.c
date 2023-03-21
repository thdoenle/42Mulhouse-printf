/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:59:37 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/10 20:37:03 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftp_get_char(char c, t_str *ret, t_lst **lst)
{
	if (ftp_lst_malloc(lst, &(ret->ptr), 1) == ERR)
		return ;
	ret->ptr[0] = c;
	ret->size = 1;
}

void	ftp_get_str(const char *s, t_param *param, t_str *ret, t_lst **lst)
{
	int	len;

	if (s == NULL)
		s = "(null)";
	len = 0;
	while (len >= 0 && s[len] && (!(param->f & PRECISION) || len < param->p))
		len++;
	if (len < 0 || ftp_lst_malloc(lst, &(ret->ptr), len) == ERR)
		return ;
	ret->size = len;
	while (len > 0)
	{
		len--;
		ret->ptr[len] = s[len];
	}
}

int	ftp_enlarge_to_width(t_param *param, t_str *ret, t_lst **lst)
{
	char	*new;
	int		to_i;
	int		i;
	int		old_i;

	if (ftp_lst_malloc(lst, &new, param->w) == ERR)
		return (ERR);
	to_i = param->w - ret->size;
	if (param->f & MINUS)
		to_i = ret->size;
	i = 0;
	old_i = 0;
	while (i < param->w)
	{
		if (((param->f & MINUS) && i >= to_i)
			|| (!(param->f & MINUS) && i < to_i))
			new[i] = ' ';
		else
			new[i] = ret->ptr[old_i++];
		i++;
	}
	ftp_lst_free(lst, ret->ptr);
	ret->ptr = new;
	ret->size = param->w;
	return (0);
}

void	ftp_convert_to_str(t_param *param, t_str *ret, t_lst **lst, va_list *va)
{
	if (param->f & (MINUS | PRECISION))
		param->f &= ~ZERO;
	if (param->type == 'c')
		ftp_get_char(va_arg(*va, int), ret, lst);
	else if (param->type == 's')
		ftp_get_str(va_arg(*va, const char *), param, ret, lst);
	else if (param->type == 'p')
		ftp_get_hex_addr(va_arg(*va, unsigned long long), param, ret, lst);
	else if (param->type == 'd' || param->type == 'i')
		ftp_get_int(va_arg(*va, int), param, ret, lst);
	else if (param->type == 'u')
		ftp_get_uint(va_arg(*va, unsigned int), param, ret, lst);
	else if (param->type == 'x')
		ftp_get_hex_uint(va_arg(*va, unsigned int), param, ret, lst);
	else if (param->type == 'X')
		ftp_get_hex_uint(va_arg(*va, unsigned int), param, ret, lst);
	if (ret->ptr == NULL)
		return ;
	if (ret->size < param->w && ftp_enlarge_to_width(param, ret, lst) == ERR)
		ret->ptr = NULL;
}
