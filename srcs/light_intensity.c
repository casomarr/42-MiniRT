/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intensity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:55:14 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/18 17:35:36 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*The closer the object is to the light source, the
higher is the light intensity reflected on the object.
This equation is called Inverse Square Law.*/
int	distance_light_object(t_data *data)
{
	t_vec result;
	
	result = sqrt((point_y ^ 2) + (point_x ^ 2));
	/*rajouter calcul pour que result = la valeur par
	laquelle la couleur doit etre multipliee*/
	return result;
}
/*Bidirectional Reflectance Distribution Function :
function that takes as parameters the direction of
the ray when entering and leaving the object. If the
angle that we get is narrow, the light intensity will
be higher (more intense).*/
int	brdf(t_data *data)
{
	
}

/*Returns the intensity of the shadowing (by how much does
the pixel color has to be toned down)*/
int	shadows(t_data *data)
{
	
}
