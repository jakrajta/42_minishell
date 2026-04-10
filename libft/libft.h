/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:36:07 by jakrajic          #+#    #+#             */
/*   Updated: 2025/09/18 17:36:07 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

# define BUFFER_SIZE 5

/* ----------- STRUCT ----------- */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ----------- LIBFT FUNCTIONS ----------- */
char				*ft_itoa(int n);
char				**ft_split(const char *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strrchr(const char *str, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_bzero(void *str, size_t n);
void				*ft_calloc(size_t count, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dest, void const *src, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlcat(char *dest, const char *src, size_t destsize);
size_t				ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t				ft_strlen(const char *str);

/* ----------- BONUS LIST FUNCTIONS ----------- */
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

/* ----------- FT_PRINTF FUNCTIONS ----------- */
int					ft_printf(const char *format, ...);
int					print_char(int c);
int					print_str(char *str);
int					print_ptr(void *ptr);
int					print_digits(int n);
int					print_udigits(unsigned int n);
int					print_hex_lower(unsigned int n);
int					print_hex_upper(unsigned int n);
int					print_percent(void);

/* ----------- GET_NEXT_LINE ----------------- */
char				*get_next_line(int fd);
char				*gnlft_strchr(const char *str, int c);
size_t				gnlft_strlen(const char *str);
char				*gnlft_strdup(const char *str);
char				*gnlft_strjoin(const char *str1, const char *str2);
char				*gnlft_substr(const char *str, unsigned int start,
						size_t len);

#endif
