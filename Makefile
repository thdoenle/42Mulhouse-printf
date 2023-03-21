SRCS	= ft_printf.c ftp_lst_allocation.c ftp_parse_params.c ftp_check.c \
	ftp_conversion.c ftp_num_conversion.c ftp_num_conversion_utils.c
OBJS	= $(SRCS:%.c=%.o)
HEADER	= ft_printf.h
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -rf
AR		= ar rc
NAME	= libftprintf.a

$(NAME): $(OBJS)
	$(AR) $@ $?

all: $(NAME) bonus

bonus: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
