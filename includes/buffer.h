#ifndef BUFFER_H
# define BUFFER_H

typedef	struct		s_buff
{
	char			*buf_el;
	int				size_buf;
	int				fill_buf;
}					t_buff;

t_buff				*create_buff(int size);
void				realloc_buff_add(t_buff *buf, int new_size);
void				free_buffer(t_buff **buf);
int					read_flow_directly(t_buff *buffer, int flow, int num);

#endif
