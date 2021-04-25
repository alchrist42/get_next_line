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



int	ft_create_line(t_list **begin_flow, char **line)
{
	t_list	*flow;
	char	*temp;
	size_t	copied;
	char 	*dst;

	*line = malloc(sizeof(**line) * (*begin_flow)->lenght);
	if (!*line)
		return (-1);
	flow = *begin_flow;
	printf("Start copy string (%zu)\n", (*begin_flow)->lenght);
	dst = *line;
	while (true) // копируем данные с буфферов
	{
		printf(" end = %zu, start = %zu, content = |%s|\n", flow->end_pos, flow->start_pos, flow->content + flow->start_pos);
		copied = ft_strlcpy(dst, flow->content + flow->start_pos, flow->end_pos - flow->start_pos + 1);
		printf(" copied: %zu\n", copied);
		dst += copied;
		if (flow->flow)
			flow = flow->flow;
		else
			break;
	}
	(*begin_flow)->start_pos = flow->start_pos + copied + 1;
	printf("Complete string: |%s|\n", *line);
	printf("Start swap last <-> first\n");
	if (*begin_flow != flow) // swap content between first and last. 
	{
		// (*begin_flow)->start_pos = flow->start_pos;
		(*begin_flow)->end_pos = flow->end_pos;
		temp = (*begin_flow)->content;
		(*begin_flow)->content = flow->content;
		flow->content = temp;
	}
	(*begin_flow)->lenght = 0;
	
	// free *
	(*begin_flow)->flow = NULL;	//зануляем поддерево. поидее это сделает фри

	return (1);
}

int	ft_check_buf(t_list **begin_flow, t_list **flow, int lenght, char **line)
{
	size_t	i;

	printf("Checker (%p):\n start = %zu\n end = %zu\n all_cont = |", *flow, (*flow)->start_pos, (*flow)->end_pos);
	
	for (int j = 0; j < (*flow)->buffer_size; j++)
		printf("%c", (*flow)->content[j]);
	printf("|\n\n");
	// if (lenght == 0 && (*flow)->start_pos < (*flow)->end_pos) // reach end of file
	// {
	// 	printf("FILE END\n");
	// 	return (ft_create_line(begin_flow, line));

	// }

	if (lenght > 0)
		(*flow)->end_pos = (*flow)->end_pos + lenght;

	i = 0;
	while ((*flow)->start_pos + i < (*flow)->end_pos)
	{
		(*begin_flow)->lenght++;
		if ((*flow)->content[(*flow)->start_pos + i] == '\n')
		{
			(*flow)->content[(*flow)->start_pos + i] = 0;
			// (*flow)->start_pos += i + 1;
			return (ft_create_line(begin_flow, line));
		}
		i++;
	}
	if ((*flow)->buffer_size - (*flow)->end_pos < BUFFER_SIZE) // место в текущем листе закончилось
	{
		printf("Created new structure %p -> ", *flow);
		(*flow)->flow = ft_lstnew((*flow)->fd);
		*flow = (*flow)->flow;
		printf("%p\n", *flow);
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

	printf(" Structure created.\n");
	readen = ft_check_buf(&begin_flow, &flow, -1, line);
	// if (!readen)
	// 	return (0);
	printf(" first check\n");
	while (true)
	{
		readen = (read(fd, flow->content + flow->end_pos, BUFFER_SIZE)); // read to buffer
		if (readen < 0)
		{	
			// ft_lstdelone(&begin, flow_lst);
			return (-1);
		}
		if (readen == 0)
		{	
			if (flow->start_pos <= flow->end_pos)
				return (ft_create_line(&begin_flow, line));
			else
				return (0);
		}
		// if (readen < BUFFER_SIZE)
		// 	flow->content[flow->end_pos + readen] = '\n';

		readen = ft_check_buf(&begin_flow, &flow, readen, line);; // чекаем буффер на переносы строк.. добавляем лист при необходимости
		
		if (readen < 0)
			return (-1);
		
		if (readen == 1)
			return (1);

		// if (readen < BUFFER_SIZE)
		// 	return ("abc");
	}
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *s;
	for (int i = 0; i < 6; i++)
		printf("\n------ %i -------\n %d: |%s|\n----------------\n\n", i, get_next_line(fd, &s), s);
	// sleep(2);
	// printf("|%s|\n\n\n", s);

	// printf("%d: ", get_next_line(fd, &s));
	// printf("|%s|\n", s);
	close(fd);
}