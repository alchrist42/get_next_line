#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define CONTENT_MIN_SIZE 4096

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_list
{
	int				fd;
	size_t			lenght;
	size_t			start;
	size_t			end;
	size_t			buffer_size;
	char			*content;
	struct s_list	*flow;
	struct s_list	*next;
}					t_list;

int		get_next_line(int fd, char **line);

t_list	*ft_find_or_create_elem(t_list **begin, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_create_line(t_list **begin_flow, t_list *flow, char **line);
int		ft_check_buf(t_list **begin_flow, t_list **flow,
			int lenght, char **line);

t_list	*ft_lstnew(int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstfind(t_list *begin_list, int fd);
int		ft_lstclear(t_list **lst);
int		ft_lst_delflow(t_list **begin, t_list *begin_flow);

#endif