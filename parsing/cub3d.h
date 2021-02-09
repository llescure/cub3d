/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:18:00 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 17:20:06 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_colour {
	int	red;
	int	green;
	int	blue;
}	t_colour ;

typedef struct	s_resolution {
	int axe_x;
	int axe_y;
}	t_resolution ;

typedef struct	s_param {
	char	*colour;
	int		resolution;
	int		sprite;
	int		ground_colour;
	int		north_texture;
	int		south_texture;
	int		west_texture;
	int		east_texture;
}	t_param ;

size_t		ft_strlen(char *str);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_atoi_cub3d(char *str, int i);
int			ft_is_string(char *s1, char *s2);
int			file_is_cub(char *str);
int			calculate_nb_chains(char *str);
int			ft_biggest_line_len(char *str);
int			read_map(int fd, char *str, char *map);
char		*only_map(char *str);
char		**recup_map(char **str, int largeur, int longueur);
char		**creation_tableau_map(char *map, char **liste, int max_length);
char		**creation_tableau_param(char *str, char **liste);
int			verif_walls_extremite(char *str, int longueur);
int			verif_symbols(char *str);
int			verif_holes_walls(char **map, int largeur, int longueur);
int			verif_first_last_string_map(char *str);
char		*only_parameters_in_map(char *str);
int			parametres_map(char *str);
int			verification_map(char **liste, int largeur, int max_length);
char		*recuperer_param_numbers(char *str, char *res, int i);
int			resolution_param(char *str);
int			recuperation_adresse_param(char *str);
int			colour_params(char *str);
int			parsing_map(char *str);


#endif
