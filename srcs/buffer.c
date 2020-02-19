#include "buffer.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

t_buff	*create_buff(int size)
{
	t_buff *tmp;

	tmp = (t_buff*)malloc(sizeof(t_buff));
	if (tmp == 0)
		return (0);
	if (tmp)
	{
		tmp->buf_el = (char*)malloc(sizeof(char) * size);
		tmp->size_buf = size;
		tmp->fill_buf = 0;
		tmp->buf_el[0] = 0;
	}
	return (tmp);
}

void	realloc_buff_add(t_buff *buf, int new_size)
{
	char	*new_b;
	int		i;

	if (new_size <= buf->size_buf)
		return ;
	new_b = (char*)malloc(sizeof(char) * new_size);
	i = 0;
	while (i < buf->size_buf)
	{
		new_b[i] = buf->buf_el[i];
		i++;
	}
	free(buf->buf_el);
	buf->buf_el = new_b;
	buf->size_buf = new_size;
}

void	free_buffer(t_buff **buf)
{
	free((*buf)->buf_el);
	free(*buf);
}

int		read_flow_directly(t_buff *buffer, int flow, int num)
{
	int	read_count;

	if (buffer->size_buf - buffer->fill_buf < num + 2)
		realloc_buff_add(buffer, buffer->fill_buf + num + 2);
	read_count = read(flow, &(buffer->buf_el[buffer->fill_buf]), num);
	buffer->fill_buf += read_count;
	buffer->buf_el[buffer->fill_buf] = '\0';
	return (read_count);
}
