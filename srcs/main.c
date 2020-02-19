#include "buffer.h"
#include "split_ws.h"
#include "str_func.h"
#include "header.h"
#include "input1.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int			file_open(int *fd, char *file_name)
{
	*fd = open(file_name, O_RDWR);
	if (*fd < 0)
	{
		print_map_error();
		return (0);
	}
	return (1);
}

void		read_file(int fd)
{
	int			res_read;
	t_buff		*buffer;
	t_params	map_param;

	res_read = 0;
	buffer = create_buff(400000);
	res_read = read_map_from_file(buffer, fd, &map_param);
	if (res_read == 0)
		print_map_error();
	else if (!count_bsq1(&(buffer->buf_el[res_read]), &map_param))
		print_map_error();
	free_buffer(&buffer);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		i;

	if (argc == 1)
		read_file(0);
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (file_open(&fd, argv[i]) != 0)
			{
				read_file(fd);
				close(fd);
			}
			i++;
			if (i != argc)
				ft_putchar('\n');
		}
	}
}
