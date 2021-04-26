#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


# define CONTENT_MIN_SIZE 4096
// # define BUFFER_SIZE 8 //todo del


# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>


#include <fcntl.h> //todo del
#include <stdio.h> //todo del

typedef struct s_list
{
	int				fd;
	size_t			lenght;
	size_t			start_pos;
	size_t			end_pos;
	size_t			buffer_size;
	char			*content;
	struct s_list	*flow;
	struct s_list	*next;
}					t_list;

int		get_next_line(int fd, char **line);

t_list	*ft_lstnew(int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstfind(t_list *begin_list, int fd);
void	ft_lstclear(t_list **lst); //, void (*del)(void *));
int		ft_lst_delflow(t_list **begin, t_list *begin_flow);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif