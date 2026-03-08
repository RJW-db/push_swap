/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   library.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 22:42:51 by rjw           #+#    #+#                 */
/*   Updated: 2026/03/06 18:01:42 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define MAX_FDS 1024

# define SPECIFIER "csdiupxX%"

# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <time.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>

# include <stdio.h>
# include <memory.h>
# include <limits.h>
# include <stdint.h>
# include <ctype.h>

//	libft, linked lists
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//	ft_printf
typedef struct p_print
{
	const char		*fmt;
	short			spec;
	va_list			va;
	int				mal;
	char			*str;
	int				i;
	int				k;
	bool			count_or_str;
}	t_p;

typedef struct s_flags
{
	char	sp;
	bool	space;
	bool	plus;
	bool	dash;
	bool	zero;
	bool	hash;
	short	hsh;
	int		width;
	bool	dot;
	int		prec;
	int		f_len;
	int		ap_len;
	bool	minus;
	char	sign;
	long	nbr;
	char	*base;
	short	b_num;
	char	prefix[3];
	bool	stop;
	va_list	count;
}	t_fl;

typedef int				(*t_bns_count) (t_p *, t_fl *);
typedef void			(*t_bns_str) (t_p *, t_fl *);

//	String Manipulation Functions
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	free_2d_arr(char **arr);

size_t	ft_cpy_str(char *dst, const char *src);
size_t	ft_cpy_n_chr(char *dst, const char c, size_t n);
size_t	ft_cpy_num(char *dst, const char *src, size_t num);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);

int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

//	ASCII Functions
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

//	Memory Functions
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_free_str(char *str);

//	List Functions
t_list	*ft_nodenew(void *content);
void	ft_nodeadd_front(t_list **lst, t_list *new);
void	ft_nodeadd_back(t_list **lst, t_list *new);
int		ft_nodesize(t_list *lst);
t_list	*ft_nodelast(t_list *lst);
void	ft_nodedelone(t_list *lst, void (*del)(void*));
void	ft_nodeclear(t_list **lst, void (*del)(void*));
void	ft_nodeiter(t_list *lst, void (*f)(void *));
t_list	*ft_nodemap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//	File Descriptor and I/O Functions
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);

//	Get_Next_line
char	*get_next_line(int fd);

//	ft_printf
int		ft_printf_fd(int fd, const char *format, ...);
int		ft_printf(const char *fmt, ...);
int		ft_format(t_p *p);

int		parse_format(t_p *c, t_fl *f, int i);
int		flag_check(t_p *c, t_fl *f);

int		spec_count_one(t_p *c, t_fl *f);
int		spec_count_two(t_p *c, t_fl *f);
void	spec_str_one(t_p *p, t_fl *f);
void	spec_str_two(t_p *p, t_fl *f);

int		unsigned_count(t_fl *f, unsigned long n);
int		signed_count(int n);
int		signed_decimal_base(char *str, int n);
int		ft_ultoa_base(t_fl *f, unsigned long n, char *str);

int		chr_bonus_count(t_p *c, t_fl *f);
void	chr_bonus(t_p *p, t_fl *f);
int		str_bonus_count(t_p *c, t_fl *f);
void	str_bonus(t_p *p, t_fl *f);
int		int_bonus_count(t_p *c, t_fl *f);
void	int_bonus(t_p *p, t_fl *f);
void	nbr_bonus(t_p *p, t_fl *f);
int		nbr_bonus_count(t_p *c, t_fl *f);

#endif
