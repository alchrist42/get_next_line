#include "get_next_line.h"


t_list	*ft_find_or_create_elem(t_list **begin, int fd)
{
	t_list	*current;

	current = ft_lstfind(*begin, fd);
	if (current)
		return (current);
	current = ft_lstnew(fd);
	if (!current)
		return (NULL);
	ft_lstadd_front(begin, current);
	return (current);
}

int	ft_check_buf(t_list **begin_flow, t_list *flow, int lenght, int fd)
{
	while (flow->start_pos < flow->end_pos)
	{
		if (flow->content[flow->start_pos] =='\n')
		{
			*s = ft_create_line(begin_flow, flow);
		}
		flow->start_pos++;
	}


	return i;
}



int get_next_line(int fd, char **line)
{
	static t_list	*begin;
	t_list			*begin_flow;
	t_list 			*flow;
	int				readen;

	begin_flow = ft_find_or_create_elem(&begin, fd);
	flow = begin_flow;
	if (!begin || !flow)
		return (-1);

	readen = ft_check_buf(flow, flow->end_pos - flow->start_pos, fd);
	

	readen = flow;
	while (true)
	{
		
		readen = (read(fd, flow->content + flow->end_pos, BUFFER_SIZE)); // read to buffer
		if (readen < 0)
		{	
			// ft_lstdelone(&begin, flow_lst);
			return (-1);
		}
		if (readen < BUFFER_SIZE)
			flow->content[flow->end_pos + readen] = '\n';

		readen = ft_check_buf(flow, readen); // чекаем буффер на переносы строк.. добавляем лист при необходимости
		if (readen < 0)
			return (-1);
		if (readen < BUFFER_SIZE)
			return ("abc");
		
	}
}