#include <unistd.h>

void	print_map_error(void)
{
	write(2, "map error\n", 10);
}
