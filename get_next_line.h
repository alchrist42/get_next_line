#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdbool.h>

CONTENT_MIN_SIZE = 4096;
BUFFER_SIZE = 512; //todo del

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

#endif