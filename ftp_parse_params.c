/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_parse_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:05:03 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/10 15:16:32 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_is_flag(const char c, char *flags)
{
	while (*flags)
	{
		if (c == *flags)
			return (1);
		flags++;
	}
	return (0);
}

void	ftp_parse_flags(const char **format, t_param *param)
{
	while (ftp_is_flag(**format, FLAG_STR))
	{
		if (**format == '-')
			param->f |= MINUS;
		else if (**format == '0')
			param->f |= ZERO;
		else if (**format == '#')
			param->f |= HASH;
		else if (**format == ' ')
			param->f |= SPACE;
		else if (**format == '+')
			param->f |= PLUS;
		(*format)++;
	}
}

int	ftp_atoi(const char **format)
{
	int	num;

	num = 0;
	while (**format >= '0' && **format <= '9')
	{
		num = num * 10 + (**format - '0');
		(*format)++;
		if (num < 0)
			return (ERR);
	}
	return (num);
}

int	ftp_parse_params(const char **format, t_param *param)
{
	param->f = 0;
	param->p = 1;
	param->w = 0;
	ftp_parse_flags(format, param);
	if (**format >= '1' && **format <= '9')
	{
		param->f |= WIDTH;
		param->w = ftp_atoi(format);
		if (param->w == ERR)
			return (ERR);
	}
	if (**format == '.')
	{
		param->f |= PRECISION;
		(*format)++;
		param->p = ftp_atoi(format);
		if (param->p == ERR)
			return (ERR);
	}
	return (0);
}
