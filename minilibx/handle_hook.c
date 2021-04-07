/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:40:45 by llescure          #+#    #+#             */
/*   Updated: 2021/04/07 15:35:05 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

int	move_perso(t_data *data)
{
	float speed;

	if (data->param.resolution.axe_y > data->param.resolution.axe_x)
		speed = 0.1;
	else
		speed = 0.1;
	if (data->param.map.tab_map[(int)(data->param.perso.position_y +
				data->param.perso.diry * speed)][(int)
			(data->param.perso.position_x + data->param.perso.dirx * speed)]
			== '0' || data->param.map.tab_map[(int)
			(data->param.perso.position_y + data->param.perso.diry * speed)]
			[(int)(data->param.perso.position_x +
				data->param.perso.dirx * speed)] ==
			data->param.perso.orientation)
	{
		data->param.perso.position_x += data->param.perso.dirx * speed;
		data->param.perso.position_y += data->param.perso.diry * speed;
	}
//	printf("speed1: %f\n", data->param.perso.dirx);
//	printf("speed2: %f\n", data->param.perso.diry);
	return (0);
}

int	launch_hook(t_data *data)
{
	data->ray.posX = (double)data->param.perso.position_y;
	data->ray.posY = (double)data->param.perso.position_x;
	if (data->win_ptr == NULL)
		return (-1);
	raycasting(data, &data->ray);
	draw_minimap(data);
	if (data->param.perso.dirx != 0 || data->param.perso.diry != 0)
		move_perso(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr,
			data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_lenght,
			&data->img.endian);
	return (0);
}

int	create_window(t_data *data)
{
	int lenght;
	int width;

	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		printf("ERROR\nCouldn't start mlx_init");
		return (-1);
	}
	mlx_get_screen_size(data->mlx_ptr, &lenght, &width);
	if (lenght < data->param.resolution.axe_x)
		data->param.resolution.axe_x = lenght;
	if (width < data->param.resolution.axe_y)
		data->param.resolution.axe_y = width;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->param.resolution.axe_x,
			data->param.resolution.axe_y, "my window");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		printf("ERROR\nCouldn't open a window");
		return (-1);
	}
	return (0);
}

int		initialize_mlx(t_data *data)
{
	initialisation_orientation(&data->param, &data->ray);

	data->img.img = mlx_new_image(data->mlx_ptr, data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_lenght, &data->img.endian);
	get_textures(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->win_ptr, 33, (1L << 17), &click_close, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &release_key, data);
	mlx_loop_hook(data->mlx_ptr, &launch_hook, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}
