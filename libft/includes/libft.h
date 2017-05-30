/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:42:28 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/14 01:24:06 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

size_t				ft_strlen(const char *s);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr(long int nbr);
char				*ft_strdup(const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putnbr_fd(long int nbr, int fd);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(char *str);
int					ft_atoi_base(const char *str, int str_base);
void				*ft_memset(void *str, int c, size_t length);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *str1, const void *str2, size_t n);
void				*ft_memccpy(void *str1, const void *src, int c, size_t n);
void				*ft_memmove(void *str1, const void *str2, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(char *string, int c);
char				*ft_strrchr(const char *string, int c);
char				*ft_strstr(const char *src, const char *tofind);
char				*ft_strnstr(const char *src, const char *t, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
int					ft_isalpha(int c);
int					ft_isdigit(int digit);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *str);
void				ft_striter(char *str, void (*f)(char *));
void				ft_striteri(char *str, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *str, char (*f)(char));
char				*ft_strmapi(char const *str, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_itoabase_uint(unsigned long int nbr, char *base);
char				*ft_strtolower(char *string);

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

char				*ft_str_replace(char *toreplace, char *tof, char *toset);
void				ft_lstaddend(t_list **list, t_list *toadd);
int					ft_strposition(char *from, char *tofind);
char				*ft_strdelchar(char *str, char c);
size_t				ft_lenarray(void **array);
char				**ft_set_null(char **buf);
int					ft_count_lines(char *buffer);
char				*ft_add_in(char *buffer, char *toadd, int oct, int i);
int					ft_check_fd(int *array, int const fd);
char				*ft_strndup(char *string, size_t size);
char				*ft_charcat(char *str, char toadd);
char				*ft_strreverse(char *str);
#endif
