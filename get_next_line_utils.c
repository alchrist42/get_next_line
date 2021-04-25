#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(*elem));
	if (elem)
	{
		elem->fd = fd;
		elem->lenght = 0;
		elem->start_pos = 0;
		elem->end_pos = 0;
		elem->flow = NULL;
		elem->next = NULL;
		if (BUFFER_SIZE < CONTENT_MIN_SIZE)
			elem->buffer_size = CONTENT_MIN_SIZE;
		else
			elem->buffer_size = BUFFER_SIZE;
		elem->content = malloc(sizeof(*elem->content) * elem->buffer_size); //todo
		if (!elem->content)
		{
			free(elem);
			elem = NULL;
		}
	}
	return (elem);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lstfind(t_list *begin_list, int fd)
{
	while (begin_list)
	{
		if (begin_list->fd == fd)
			return (begin_list);
		begin_list = begin_list->next;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (dst && i + 1 < dstsize)
			dst[i] = src[i];
		i++;
	}
	if (dstsize && dst)
	{
		if (dstsize - 1 < i)
			dst[dstsize - 1] = 0;
		else
			dst[i] = 0;
	}
	return (i);
}
	
char	*ft_strncpy(char *dest, char *src, size_t n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}