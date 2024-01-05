#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		printf("Error\nUsage ./miniRT <file.rt>\n");
		return (0);
	}
	if (parsing(argv[1], &data) == false)
	{
		ft_dprintf(2, "Error\nParsing failed\n");
		return (0); //need to change this return to 1 and continue test from action
	}
}
