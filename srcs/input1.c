#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "header.h"
#include "str_func.h"
#include "buffer.h"
#include "split_ws.h"
#include "str_func.h"
#include "header.h"

#include <stdio.h>

#define BUFFIN_SIZE 8192000

int		read_parameters1(char *str, int length_line, t_params *map_param)
{
	if (length_line < 4)
		return (0);
	map_param->full = str[length_line - 1];
	map_param->obstacle = str[length_line - 2];
	map_param->empty = str[length_line - 3];
	map_param->lines = ft_atoi1(str, length_line - 3);
	if (map_param->lines == 0)
		return (0);
	if (map_param->full == map_param->obstacle ||
		map_param->obstacle == map_param->empty ||
		map_param->empty == map_param->full)
		return (0);
	return (1);
}

int		get_length_first_line(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != '\n')
	{
		len++;
	}
	if (str[len] != '\n')
		return (0);
	else
		return (len);
}

int		count_w_map(char *str, int start_str, int *start_pos_w)
{
	while (str[*start_pos_w] && str[*start_pos_w] != '\n')
		*start_pos_w = *start_pos_w + 1;
	if (str[*start_pos_w] != '\n')
		return (0);
	else
		return (*start_pos_w - start_str);
}

void	read_fl(t_buff *buffer, int fd, int size_buf)
{
	int read_count;

	if (fd != 0)
		read_count = read_flow_directly(buffer, fd, size_buf);
	else
	{
		realloc_buff_add(buffer, buffer->fill_buf + size_buf + 2);
		read_count = read_flow_directly(buffer, fd, 8192);
		while (read_count != 0)
			read_count = read_flow_directly(buffer, fd, 8192);
	}
}

int		read_map_from_file(t_buff *buffer, int fd, t_params *map_param)
{
	int	len;
	int	w_sizef;
	int read_count;
	int w_line;

	w_line = 0;
	read_count = read_flow_directly(buffer, fd, 15);
	len = get_length_first_line(buffer->buf_el);
	if (!(read_parameters1(buffer->buf_el, len, map_param)))
		return (0);
	w_sizef = len + 1;
	while (read_count != 0 && w_line == 0)
	{
		read_count = read_flow_directly(buffer, fd, 8177);
		w_line = count_w_map(buffer->buf_el, len + 1, &w_sizef);
	}
	if (w_line <= 0)
		return (0);
	w_sizef = len + (w_line + 1) * map_param->lines + 1;
	read_fl(buffer, fd, (len + map_param->lines + (map_param->lines *
								w_line)) - buffer->fill_buf + 3);
	if (w_sizef != buffer->fill_buf)
		return (0);
	map_param->width = w_line;
	return (len + 1);
}
