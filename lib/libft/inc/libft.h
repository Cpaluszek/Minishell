/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:47 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:02:47 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdarg.h>
# define NULL_STR "(null)"
# define HEX_BASE_LOWER "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*	Checker */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isspace(int c);

/*	Str	*/
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_size_tab(char **tab);
int		ft_strcmp(const char *first, const char *second);
int		ft_strncmp(const char *first, const char *second, size_t length);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_and_free(char *s1, const char *s2);
char	*ft_strjoin_and_free_s2(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	**ft_tab_strdup(char **tab);
char	**ft_merge_tab(char **tab1, char **tab2);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_striteri(char *s, char (*f)(unsigned int, char*));
int		ft_is_inside(char c, const char *base);

/* Memory	*/
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_free(void *ptr);
char	**ft_free_split(char **strs);

/* Input-Output */
void	ft_putchar_fd(const char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);

/*	ft_printf	*/
int		ft_printf(const char *input, ...);
int		ft_pick_conversion(const char c, va_list args);
int		ft_print_decimal(const int nb);
int		ft_print_string(const char *str);
int		ft_print_pointer(size_t ptr);
int		ft_print_lower_hex(size_t nb);
int		ft_print_upper_hex(size_t nb);
int		ft_print_unsigned_int(unsigned int nb);
int		ft_print_size_t_base(size_t nb, char *base, size_t base_len);

/*	ft_printf_fd	*/
int		ft_printf_fd(int fd, const char *input, ...);
int		ft_pick_conversion_fd(int fd, const char c, va_list args);
int		ft_print_decimal_fd(const int nb, int fd);
int		ft_print_string_fd(const char *str, int fd);
int		ft_print_pointer_fd(size_t ptr, int fd);
int		ft_print_lower_hex_fd(size_t nb, int fd);
int		ft_print_upper_hex_fd(size_t nb, int fd);
int		ft_print_unsigned_int_fd(unsigned int nb, int fd);
int		ft_print_size_t_base_fd(size_t nb, char *base, size_t b_len, int fd);

/*	Get Next Line */
char	*get_next_line(int fd);

/* lists	*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstsort(t_list **lst, int (*cmp)());

#endif
