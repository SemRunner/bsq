#include <stdlib.h>
#include "header.h"
#include "str_func.h"

int		min_1(int a, int b, int c)
{
	if ((a <= b) && (a <= c))
		return (a);
	if ((b <= a) && (b <= c))
		return (b);
	else
		return (c);
}

void	swap_arrays(int **arr_1, int **arr_2)
{
	int *arr_temp;

	arr_temp = *arr_1;
	*arr_1 = *arr_2;
	*arr_2 = arr_temp;
}

void	put_in_map_param(t_params *map_param, int arr_2_w, int l, int w)
{
	if (map_param->max < arr_2_w)
	{
		map_param->max = arr_2_w;
		map_param->l = l;
		map_param->w = w;
	}
}

int		ft_atoi1(char *str, int length_num)
{
	int min;
	int val;
	int i;

	min = 0;
	val = 0;
	i = 0;
	val = 0;
	while (i < length_num)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		val = (val * 10) + str[i] - 48;
		i++;
	}
	return (val);
}
