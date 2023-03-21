/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:15:20 by thdoenle          #+#    #+#             */
/*   Updated: 2022/12/10 21:00:30 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define FLAG_STR "-0# +"
# define NB_TYPES 8
# define STR_TYPES "cspdiuxX"
# define ERR -1

enum
{
	MINUS = 1 << 0,
	ZERO = 1 << 1,
	HASH = 1 << 2,
	SPACE = 1 << 3,
	PLUS = 1 << 4,
	WIDTH = 1 << 5,
	PRECISION = 1 << 6,
};

typedef struct s_lst
{
	void			*ptr;
	struct s_lst	*next;
}	t_lst;

typedef struct s_str
{
	char	*ptr;
	int		size;
}	t_str;

typedef struct s_param
{
	int		f;
	int		w;
	int		p;
	char	type;
}	t_param;

int		ft_printf(const char *format, ...);

int		ftp_lst_clear(t_lst **lst, va_list *va);
int		ftp_lst_malloc(t_lst **lst, char **ptr, size_t size);
void	ftp_lst_free(t_lst **lst, void *ptr);

void	ftp_convert(const char **format, t_str *ret, t_lst **lst, va_list *va);
int		ftp_parse_params(const char **format, t_param *param);
int		ftp_check_type(t_param *param);
void	ftp_convert_to_str(t_param *param, t_str *ret, t_lst **lst,
			va_list *va);

void	ftp_get_hex_addr(unsigned long long n, t_param *param, t_str *ret,
			t_lst **lst);
void	ftp_get_int(int n, t_param *param, t_str *ret, t_lst **lst);
char	ftp_get_preint_char(int n, t_param *param);
void	ftp_get_uint(unsigned int n, t_param *param, t_str *ret, t_lst **lst);
void	ftp_get_hex_uint(unsigned int n, t_param *param, t_str *ret,
			t_lst **lst);
void	ftp_numtoa_base(unsigned long long n, char *dest, int size, char *base);
int		ftp_numlen(unsigned long long n, int nbase);

int		ftp_write_error(const char *msg);

#endif
