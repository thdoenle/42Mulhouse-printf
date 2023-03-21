/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_num_conversion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:42:58 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/10 19:10:53 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_numlen(unsigned long long n, int nbase)
{
	int	size;

	size = 0;
	while (n)
	{
		n /= nbase;
		size++;
	}
	return (size);
}

void	ftp_numtoa_base(unsigned long long n, char *dest, int size, char *base)
{
	int	b_len;

	b_len = 0;
	while (base[b_len])
		b_len++;
	while (size > 0)
	{
		size--;
		dest[size] = base[n % b_len];
		n /= b_len;
	}
}

char	ftp_get_preint_char(int n, t_param *param)
{
	if (n < 0)
		return ('-');
	if (param->f & PLUS)
		return ('+');
	if (param->f & SPACE)
		return (' ');
	return (0);
}
