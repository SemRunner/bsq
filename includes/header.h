#ifndef HEADER_H
# define HEADER_H
# define BUFFOUT_SIZE 8192000
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <buffer.h>

typedef struct	s_params
{
	char		full;
	char		empty;
	char		obstacle;
	int			lines;
	int			width;
	int			w;
	int			l;
	int			max;
}				t_params;

void			print_map_error(void);
int				min1(int a, int b, int c);
void			put_full_chars(char *str, t_params *map_param);
int				count_bsq1(char *str, t_params *map_param);
int				bsq_calc_1(char *str, t_params *map_param);
int				bsq_calc_2(char *str, t_params *mp, int *arr_1, int *arr_2);
int				put_line_0(char *str, t_params *map_param, int *arr_2);
int				min_1(int a, int b, int c);
void			swap_arrays(int **arr_1, int **arr_2);
void			put_in_map_param(t_params *map_param, int arr_2_w, int l,
								int w);
int				ft_atoi1(char *str, int length_num);

#endif
