#include "minirt.h"

void	ft_stop(t_data *data)
{
	t_objs	*tmp;
	while (data->scene.objs != NULL)
	{
		// if (data->scene.objs->next != NULL)
		tmp = data->scene.objs->next;
		// if (data->scene.objs)
		free(data->scene.objs);
		data->scene.objs = tmp;
	}
	data->scene.objs = NULL;
	exit(EXIT_SUCCESS);

}

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
		ft_stop(&data);
		return (0); //need to change this return to 1 and continue test from action
	}
	ft_stop(&data);
	return (0);
}
