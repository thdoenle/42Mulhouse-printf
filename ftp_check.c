/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:46:17 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/07 23:59:13 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftp_init_type_str(char *type_str)
{
	int	i;

	i = 0;
	while (i < NB_TYPES)
	{
		type_str[i] = STR_TYPES[i];
		i++;
	}
}

void	ftp_remove_chars(char *s, char *type_str)
{
	int	i;

	while (*s)
	{
		i = 0;
		while (i < NB_TYPES && type_str[i] != *s)
			i++;
		if (i < NB_TYPES)
			type_str[i] = '\0';
		s++;
	}
}

int	ftp_is_in_type_str(const char type, char *type_str)
{
	int	i;

	i = 0;
	while (i < NB_TYPES && type_str[i] != type)
		i++;
	if (i == NB_TYPES)
		return (ERR);
	return (0);
}

int	ftp_check_type(t_param *param)
{
	char	type_str[NB_TYPES];

	if (param->type == '\0')
		return (ERR);
	ftp_init_type_str(type_str);
	if (param->f & (ZERO | HASH | SPACE | PLUS | PRECISION))
		ftp_remove_chars("cp", type_str);
	if (param->f & (ZERO | HASH | SPACE | PLUS))
		ftp_remove_chars("s", type_str);
	if (param->f & (HASH))
		ftp_remove_chars("di", type_str);
	if (param->f & (HASH | SPACE | PLUS))
		ftp_remove_chars("u", type_str);
	if (param->f & (SPACE | PLUS))
		ftp_remove_chars("xX", type_str);
	return (ftp_is_in_type_str(param->type, type_str));
}

int	ftp_write_error(const char *msg)
{
	unsigned long	emo1;
	unsigned long	emo2;
	unsigned long	len;

	emo1 = 0x2085999ff0;
	emo2 = 0x0a80999ff020;
	len = 0;
	while (msg[len])
		len++;
	if (write(STDERR_FILENO, &emo1, 5) == ERR
		|| write(STDERR_FILENO, msg, len) == ERR
		|| write(STDERR_FILENO, &emo2, 6) == ERR)
		return (ERR);
	return (ERR);
}
