#include <stdlib.h>
#include "header.h"
#include "str_func.h"

int		put_line_0(char *str, t_params *map_param, int *arr_2)
{
	int w;

	w = -1;
	while (++w < map_param->width)
	{
		if (str[w] == map_param->empty)
			arr_2[w] = 1;
		else if (str[w] == map_param->obstacle)
			arr_2[w] = 0;
		else
			return (0);
		put_in_map_param(map_param, arr_2[w], 0, w);
	}
	return (1);
}

int		bsq_calc_2(char *str, t_params *mp, int *arr_1, int *arr_2)
{
	int l;
	int w;

	mp->max = 0;
	l = 0;
	while (++l < mp->lines)
	{
		w = -1;
		while (++w < mp->width)
		{
			if (str[l * (mp->width + 1) + w] == mp->obstacle)
				arr_2[w] = 0;
			else if (str[l * (mp->width + 1) + w] != mp->empty)
				return (0);
			else if (w == 0)
				arr_2[w] = 1;
			else
				arr_2[w] = min_1(arr_2[w - 1], arr_1[w], arr_1[w - 1]) + 1;
			put_in_map_param(mp, arr_2[w], l, w);
		}
		swap_arrays(&arr_1, &arr_2);
	}
	return (1);
}

int		bsq_calc_1(char *str, t_params *map_param)
{
	int *arr_1;
	int *arr_2;

	arr_1 = (int*)malloc(sizeof(int) * map_param->width);
	arr_2 = (int*)malloc(sizeof(int) * map_param->width);
	put_line_0(str, map_param, arr_1);
	if (bsq_calc_2(str, map_param, arr_1, arr_2) == 0)
		return (0);
	free(arr_1);
	free(arr_2);
	return (1);
}

void	put_full_chars(char *str, t_params *map_param)
{
	int l;
	int w;

	l = map_param->l - map_param->max + 1;
	while (l <= map_param->l)
	{
		w = map_param->w - map_param->max + 1;
		while (w <= map_param->w)
		{
			str[l * (map_param->width + 1) + w] = map_param->full;
			w++;
		}
		l++;
	}
}

int		count_bsq1(char *str, t_params *map_param)
{
	int			i;
	long long	size_matrix;
	long long	buf;

	if (bsq_calc_1(str, map_param) == 0)
		return (0);
	if (map_param->max > 0)
		put_full_chars(str, map_param);
	size_matrix = map_param->lines * (map_param->width + 1);
	if (size_matrix <= BUFFOUT_SIZE)
		ft_putstr_u(str, size_matrix);
	else
	{
		i = BUFFOUT_SIZE;
		while (i <= size_matrix)
		{
			write(1, str, BUFFOUT_SIZE);
			i += BUFFOUT_SIZE;
			str = str + BUFFOUT_SIZE;
		}
		buf = size_matrix - (i - BUFFOUT_SIZE);
		write(1, str, buf);
	}
	return (1);
}
