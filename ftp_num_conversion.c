/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_num_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:20:56 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/10 20:40:21 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftp_get_hex_addr(unsigned long long n, t_param *param, t_str *ret,
			t_lst **lst)
{
	int	size;

	size = ftp_numlen(n, 16);
	if (size < param->p)
		size = param->p;
	if (size + 2 < 0 || ftp_lst_malloc(lst, &(ret->ptr), size + 2) == ERR)
		return ;
	ret->size = 2 + size;
	ret->ptr[0] = '0';
	ret->ptr[1] = 'x';
	ftp_numtoa_base(n, ret->ptr + 2, size, "0123456789abcdef");
}

void	ftp_get_int(int n, t_param *param, t_str *ret, t_lst **lst)
{
	unsigned long long	un;
	int					size;
	int					start;

	un = n;
	if (n < 0)
		un = -(unsigned long long)n;
	start = 0;
	if (n < 0 || (param->f & (SPACE | PLUS)))
		start++;
	size = ftp_numlen(un, 10);
	if (size < param->p)
		size = param->p;
	if ((param->f & ZERO) && (param->f & WIDTH) && size < param->w - start)
		size = param->w - start;
	if (size + start < 0
		|| ftp_lst_malloc(lst, &(ret->ptr), size + start) == ERR)
		return ;
	ret->size = start + size;
	if (start)
		ret->ptr[0] = ftp_get_preint_char(n, param);
	ftp_numtoa_base(un, ret->ptr + start, size, "0123456789");
}

void	ftp_get_uint(unsigned int n, t_param *param, t_str *ret, t_lst **lst)
{
	int	size;

	size = ftp_numlen(n, 10);
	if (size < param->p)
		size = param->p;
	if ((param->f & ZERO) && (param->f & WIDTH) && size < param->w)
		size = param->w;
	if (ftp_lst_malloc(lst, &(ret->ptr), size) == ERR)
		return ;
	ret->size = size;
	ftp_numtoa_base(n, ret->ptr, size, "0123456789");
}

void	ftp_get_hex_uint(unsigned int n, t_param *param, t_str *ret,
	t_lst **lst)
{
	int	size;
	int	start;

	start = 0;
	if (param->f & HASH && n)
		start = 2;
	size = ftp_numlen(n, 16);
	if (size < param->p)
		size = param->p;
	if ((param->f & ZERO) && (param->f & WIDTH) && size < param->w - start)
		size = param->w - start;
	if (size + start < 0
		|| ftp_lst_malloc(lst, &(ret->ptr), size + start) == ERR)
		return ;
	ret->size = start + size;
	if (start)
	{
		ret->ptr[0] = '0';
		ret->ptr[1] = param->type;
	}
	if (param->type == 'x')
		ftp_numtoa_base(n, ret->ptr + start, size, "0123456789abcdef");
	else if (param->type == 'X')
		ftp_numtoa_base(n, ret->ptr + start, size, "0123456789ABCDEF");
}
