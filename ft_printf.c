/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:45:46 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/11 14:01:05 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_add_to_buffer(t_str *print, t_str *str, t_lst **lst)
{
	char	*new;
	char	*ptr;
	int		i;

	if (print->size + str->size < 0
		|| ftp_lst_malloc(lst, &new, print->size + str->size) == ERR)
		return (ERR);
	i = 0;
	while (i < print->size)
	{
		new[i] = print->ptr[i];
		i++;
	}
	ptr = new + i;
	i = 0;
	while (i < str->size)
	{
		ptr[i] = str->ptr[i];
		i++;
	}
	ftp_lst_free(lst, print->ptr);
	ftp_lst_free(lst, str->ptr);
	print->ptr = new;
	print->size += str->size;
	return (0);
}

void	ftp_dup_until_conv(const char **format_ptr, t_str *str, t_lst **lst)
{
	int	i;

	i = 0;
	while ((*format_ptr)[i] && (*format_ptr)[i] != '%' && i >= 0)
		i++;
	if (i < 0 || ftp_lst_malloc(lst, &(str->ptr), i) == ERR)
		return ;
	i = 0;
	while (**format_ptr && **format_ptr != '%')
	{
		str->ptr[i] = **format_ptr;
		i++;
		(*format_ptr)++;
	}
	str->size = i;
}

void	ftp_convert(const char **format, t_str *ret, t_lst **lst, va_list *va)
{
	t_param	param;

	ret->ptr = NULL;
	(*format)++;
	if (**format == '%')
	{
		if (ftp_lst_malloc(lst, &(ret->ptr), 1) == ERR)
			return ;
		ret->ptr[0] = '%';
		ret->size = 1;
		(*format)++;
		return ;
	}
	if (ftp_parse_params(format, &param) == ERR
		&& ftp_write_error("BAD PARAMETERS"))
		return ;
	param.type = **format;
	(*format)++;
	if (ftp_check_type(&param) == ERR
		&& ftp_write_error("INVALID CONVERSION"))
		return ;
	ftp_convert_to_str(&param, ret, lst, va);
}

int	ft_printf(const char *format, ...)
{
	t_str	print;
	t_str	str;
	t_lst	*m_lst;
	va_list	va;

	print.ptr = NULL;
	print.size = 0;
	m_lst = NULL;
	va_start(va, format);
	while (*format)
	{
		if (*format == '%')
			ftp_convert(&format, &str, &m_lst, &va);
		else
			ftp_dup_until_conv(&format, &str, &m_lst);
		if (str.ptr == NULL)
			return (ftp_lst_clear(&m_lst, &va));
		if (ftp_add_to_buffer(&print, &str, &m_lst) == ERR)
			return (ftp_lst_clear(&m_lst, &va));
	}
	if (write(STDOUT_FILENO, print.ptr, print.size) == ERR)
		return (ftp_lst_clear(&m_lst, &va));
	ftp_lst_free(&m_lst, print.ptr);
	va_end(va);
	return (print.size);
}
