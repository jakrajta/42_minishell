# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 17:34:07 by jakrajic          #+#    #+#              #
#    Updated: 2025/09/18 17:34:07 by jakrajic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# ------------ LIBFT ------------
SRC = libft/ft_atoi.c \
      libft/ft_bzero.c \
      libft/ft_calloc.c \
      libft/ft_isalnum.c \
      libft/ft_isalpha.c \
      libft/ft_isascii.c \
      libft/ft_isdigit.c \
      libft/ft_isprint.c \
      libft/ft_itoa.c \
      libft/ft_memchr.c \
      libft/ft_memcmp.c \
      libft/ft_memcpy.c \
      libft/ft_memmove.c \
      libft/ft_memset.c \
      libft/ft_putchar_fd.c \
      libft/ft_putendl_fd.c \
      libft/ft_putnbr_fd.c \
      libft/ft_putstr_fd.c \
      libft/ft_split.c \
      libft/ft_strchr.c \
      libft/ft_strdup.c \
      libft/ft_striteri.c \
      libft/ft_strjoin.c \
      libft/ft_strlcat.c \
      libft/ft_strlcpy.c \
      libft/ft_strlen.c \
      libft/ft_strmapi.c \
      libft/ft_strncmp.c \
      libft/ft_strnstr.c \
      libft/ft_strrchr.c \
      libft/ft_strtrim.c \
      libft/ft_substr.c \
      libft/ft_tolower.c \
      libft/ft_toupper.c

BONUS = libft/ft_lstadd_back.c \
        libft/ft_lstadd_front.c \
        libft/ft_lstclear.c \
        libft/ft_lstdelone.c \
        libft/ft_lstiter.c \
        libft/ft_lstlast.c \
        libft/ft_lstmap.c \
        libft/ft_lstnew.c \
        libft/ft_lstsize.c

# ------------ FT_PRINTF ------------
PRINTF = ft_printf/ft_printf.c \
         ft_printf/print_char.c \
         ft_printf/print_str.c \
         ft_printf/print_digits.c \
         ft_printf/print_hex_lower.c \
         ft_printf/print_hex_upper.c \
         ft_printf/print_ptr.c \
         ft_printf/print_udigits.c \
         ft_printf/print_percent.c

#-------------- GNL ---------------
GNL = gnl/get_next_line.c \
      gnl/get_next_line_utils.c
      
# ------------ OBJECTS ------------
OBJS = $(SRC:.c=.o)
OBJSB = $(BONUS:.c=.o)
OBJSP = $(PRINTF:.c=.o)
OBJSG = $(GNL:.c=.o)

# ------------ COMPILER ------------
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

# ------------ RULES ------------
all: $(NAME)

$(NAME): $(OBJS) $(OBJSB) $(OBJSP) $(OBJSG)
	ar rcs $(NAME) $(OBJS) $(OBJSB) $(OBJSP) $(OBJSG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSB) $(OBJSP) $(OBJSG)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus

.SILENT: