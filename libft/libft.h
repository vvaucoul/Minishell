/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:31:39 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 17:13:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, char c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *s);

void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*));
int					ft_lstadd_here(t_list *lst_to_follow, char *new_content,
	int free);

int					ft_get_next_line(int fd, char **line);

void				*ft_memalloc(size_t size);
char				*ft_realloc(char *ptr, size_t size);
int					ft_strisempty(char *str);
char				*ft_strnew(size_t size);
void				ft_freetab(char **array);
int					ft_freetab_ret(char **array, int to_return);
void				ft_freetab_onsize(char **array, int size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strequ(const char *s1, const char *s2);
void				ft_putstr(char const *s);
char				*ft_strcut(const char *str, char c);
char				*ft_straddchar(char *str, char c);
char				*ft_straddstr(char *s1, char *s2, int to_free);
int					ft_isupper(int c);
int					ft_islower(int c);
char				*ft_strjoin(const char *s1, const char *s2);
int					ft_strstartswith(char *s1, char *s2, int free_s1,
	int free_s2);
char				*ft_strcat(char *dest, char *src);
char				*ft_strtrunc_del(char *s1, char del);
char				*ft_strchangelen(char *str, int size);
int					ft_tablen(char **tabl);
int					ft_strrange(const char *str, const char *list);

#endif
